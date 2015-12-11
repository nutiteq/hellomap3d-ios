#import "VectorMapSampleBaseController.h"
#import "MyMapEventListener.h"

/*
 * Click on two locations on map and calculate offline route between them
 */
@interface OfflineRoutingController : VectorMapSampleBaseController
 - (void)setStart:(NTMapPos*)mapPos;
 - (void)setStop:(NTMapPos*)mapPos;

@property NTLocalVectorDataSource* routeDataSource;
@property NTMarker* startMarker;
@property NTMarker* stopMarker;
@property NTPackageManagerRoutingService* offlineRoutingService;

@end;

@interface  RouteClickListener : NTMapEventListener

@property (strong, nonatomic) NTMapView* mapView;
@property (strong, nonatomic) OfflineRoutingController* routingController;

//@property (strong, nonatomic) NTLocalVectorDataSource* vectorDataSource;

@property (strong, nonatomic) NTMapPos* startPos;
@property (strong, nonatomic) NTMapPos* stopPos;


@end;

/*
 * Package manager listener. Listener is notified about asynchronous events
 * about packages.
 */
@interface RoutePackageManagerListener : NTPackageManagerListener

- (void)onPackageListUpdated;
- (void)onPackageListFailed;
- (void)onPackageUpdated:(NSString*)packageId version:(int)version;
- (void)onPackageCancelled:(NSString*)packageId version:(int)version;
- (void)onPackageFailed:(NSString*)packageId version:(int)version errorType:(enum NTPackageErrorType)errorType;
- (void)onPackageStatusChanged:(NSString*)packageId version:(int)version status:(NTPackageStatus*)status;

@property OfflineRoutingController* routingController;
@property NTPackageManager* packageManager;
@end



@implementation OfflineRoutingController

- (void)viewDidLoad
{

	[super viewDidLoad];
	
	// Get the base projection set in the base class
	NTProjection* proj = [[self.mapView getOptions] getBaseProjection];
	
	// Initialize an online vector data source for base map
	_routeDataSource = [[NTLocalVectorDataSource alloc] initWithProjection:proj];
	// Initialize a vector layer with the previous data source
	NTVectorLayer* vectorLayer = [[NTVectorLayer alloc] initWithDataSource:_routeDataSource];
    
	// Add the previous vector layer to the map
	[[self.mapView getLayers] add:vectorLayer];

    
    // Create markers for start and end
    NTMarkerStyleBuilder* markerStyleBuilder = [[NTMarkerStyleBuilder alloc] init];
    [markerStyleBuilder setSize:30];
    [markerStyleBuilder setHideIfOverlapped:NO];
    [markerStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFF00FF00]]; // Green
    
    // Initial empty markers
    _startMarker = [[NTMarker alloc] initWithPos:[[NTMapPos alloc] initWithX:0 y:0] style:[markerStyleBuilder buildStyle]];
    [_startMarker setVisible:NO];
    [_routeDataSource add: _startMarker];

    // change color to Red
    [markerStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFFFF0000]];

    _stopMarker = [[NTMarker alloc] initWithPos:[[NTMapPos alloc] initWithX:0 y:0] style:[markerStyleBuilder buildStyle]];
    [_stopMarker setVisible:NO];
    [_routeDataSource add: _stopMarker];
	
	// Create a map event listener
	RouteClickListener* mapListener = [[RouteClickListener alloc] init];
	[self.mapView setMapEventListener:mapListener];
	// MapEventListener needs the data source and the layer to display balloons
	// over the clicked vector elements
    
	//[mapListener setMapView: self.mapView];
    [mapListener setRoutingController: self];

    [self.mapView setFocusPos:[proj fromWgs84:[[NTMapPos alloc] initWithX:25.662893 y:58.919365]]  durationSeconds:0];
    [self.mapView setZoom:7 durationSeconds:0];
    
    // defined PackageManger to download offline routing packages
    
    // Create folder for package manager. Package manager needs persistent writable folder.
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory, NSUserDomainMask,YES);
    NSString* appSupportDir = [paths objectAtIndex: 0];
    NSString* packagesDir = [appSupportDir stringByAppendingString:@"/packages"];
    NSError *error;
    [[NSFileManager defaultManager] createDirectoryAtPath:packagesDir withIntermediateDirectories:YES attributes:nil error:&error];
    
    NTNutiteqPackageManager* packageManager = [[NTNutiteqPackageManager alloc] initWithSource:@"routing:nutiteq.osm.car" dataFolder:packagesDir];
    
    RoutePackageManagerListener* _packageManagerListener = [[RoutePackageManagerListener alloc] init];
    
    
    // Register this controller with listener to receive notifications about events
    [_packageManagerListener setRoutingController:self];
    [_packageManagerListener setPackageManager:packageManager];
    
    // Attach package manager listener
    [packageManager setPackageManagerListener:_packageManagerListener];

    [packageManager start];
    [packageManager startPackageListDownload];

    
    // create offline routing service connected to package manager
    _offlineRoutingService = [[NTPackageManagerRoutingService alloc] initWithPackageManager:packageManager];
    
}

- (void)viewWillDisappear:(BOOL)animated
{
	// Check if the view is closing
	if ([self.navigationController.viewControllers indexOfObject:self] == NSNotFound) {
		[self.mapView setMapEventListener:nil];
	}
	
	[super viewWillDisappear:animated];
}

-(void)setStart:(NTMapPos *)mapPos{
    //[_routeDataSource removeAll];
    [_stopMarker setVisible:NO];
    [_startMarker setPos:mapPos];
    [_startMarker setVisible:YES];
    
}

-(void)setStop:(NTMapPos *)mapPos{
    [_stopMarker setPos:mapPos];
    [_stopMarker setVisible:YES];
    [self showRoute: [[_startMarker getGeometry] getCenterPos] stopPos: [[_stopMarker getGeometry] getCenterPos]];
}

// calculate route, show on map
-(void)showRoute: (NTMapPos *)startPos stopPos:(NTMapPos *)stopPos{
    

     NTMapPosVector* poses = [[NTMapPosVector alloc] init];
     [poses add:startPos];
     [poses add:stopPos];
                              
    NTRoutingRequest* request = [[NTRoutingRequest alloc] initWithProjection:[[self.mapView getOptions] getBaseProjection] points:poses];
    
    // TODO: this calculation should be in non-UI thread
    
    NTRoutingResult* route = [_offlineRoutingService calculateRoute:request];
    
    NSLog(@"route total distance: %f time %f", [route getTotalDistance], [route getTotalTime]);
    
    // show line
    [_routeDataSource add:[self calculateRouteLine: route]];
    
    //show instructions as popups
    for(int i=0;i<[[route getInstructions] size];i++){
        NTRoutingInstruction *instruction =[[route getInstructions] get:i];
        [_routeDataSource add:
         [self createRoutePoint: instruction
                          point: [[route getPoints] get:[instruction getPointIndex]]]
         ];
    }
    
    
}

-(NTBalloonPopup*) createRoutePoint: (NTRoutingInstruction*) instruction point:(NTMapPos*) pos{
    
    NSString* str = @"";
    
    switch ([instruction getAction]) {
        case NT_ROUTING_ACTION_HEAD_ON:
            str = @"head on";
            break;
        case NT_ROUTING_ACTION_FINISH:
            str = @"finish";
            break;
        case NT_ROUTING_ACTION_TURN_LEFT:
            str = @"turn left";
            break;
        case NT_ROUTING_ACTION_TURN_RIGHT:
            str = @"turn right";
            break;
        case NT_ROUTING_ACTION_UTURN:
            str = @"u turn";
            break;
        case NT_ROUTING_ACTION_NO_TURN:
        case NT_ROUTING_ACTION_GO_STRAIGHT:
            str = @"continue";
            break;
        case NT_ROUTING_ACTION_REACH_VIA_LOCATION:
            str = @"stopover";
            break;
        case NT_ROUTING_ACTION_ENTER_AGAINST_ALLOWED_DIRECTION:
            str = @"enter against allowed direction";
            break;
        case NT_ROUTING_ACTION_LEAVE_AGAINST_ALLOWED_DIRECTION:
            break;
        case NT_ROUTING_ACTION_ENTER_ROUNDABOUT:
            str = @"enter roundabout";
            break;
        case NT_ROUTING_ACTION_STAY_ON_ROUNDABOUT:
            str = @"stay on roundabout";
            break;
        case NT_ROUTING_ACTION_LEAVE_ROUNDABOUT:
            str = @"leave roundabout";
            break;
        case NT_ROUTING_ACTION_START_AT_END_OF_STREET:
            str = @"start at end of street";
            break;
    }
    
    NSString* desc =[NSString stringWithFormat:@"%@ \nazimuth:  %f\ndistance: %f m\ntime: %f s\nTurnAngle: %f deg",[instruction getStreetName],
                     [instruction getAzimuth],
                     [instruction getDistance],
                     [instruction getTime],
                     [instruction getTurnAngle]
                     ];
    
    NTBalloonPopupStyleBuilder* balloonPopupStyleBuilder = [[NTBalloonPopupStyleBuilder alloc] init];
    
    NTBalloonPopup* popup = [[NTBalloonPopup alloc] initWithPos:pos
                                                           style:[balloonPopupStyleBuilder buildStyle]
                                                           title:str
                                                            desc:desc];
    


    NSLog(@"Instruction: %@ (%@)", str, desc);
    
    return popup;
}

-(NTLine*) calculateRouteLine: (NTRoutingResult*) result{
 
    // style for the line
    NTLineStyleBuilder* lineStyleBuilder = [[NTLineStyleBuilder alloc] init];
    [lineStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFFAAAAAA]];
    [lineStyleBuilder setLineJointType:NT_LINE_JOINT_TYPE_ROUND];
    [lineStyleBuilder setStretchFactor:2];
    [lineStyleBuilder setWidth:12];
    
    return [[NTLine alloc] initWithPoses:[result getPoints] style:[lineStyleBuilder buildStyle]];

    
    
}

@end

@implementation RouteClickListener

-(void)onMapMoved
{
    // do nothing
}

-(void)onMapClicked:(NTMapClickInfo*)mapClickInfo
{
    // set start and end pos
    
    if ([mapClickInfo getClickType] == NT_CLICK_TYPE_LONG) {
        NTMapPos* clickPos = [mapClickInfo getClickPos];
        //NTMapPos* wgs84Clickpos = [[[_mapView getOptions] getBaseProjection] toWgs84:clickPos];
        
      //  NSLog(@"onMapClicked: %@", [NSString stringWithFormat:@"%f, %f", [wgs84Clickpos getY], [wgs84Clickpos getX]]);
        
        if(_startPos == nil){
            _startPos = clickPos;
            [_routingController setStart: clickPos];
            
        }else if (_stopPos == nil){
            
            _stopPos = clickPos;
            
            [_routingController setStop: clickPos];
            //setStopMarker(clickPos);
            //showRoute(startPos, stopPos);
            
            // restart to force new route next time
            _startPos = nil;
            _stopPos = nil;
        }
    }
}

-(void)onVectorElementClicked:(NTVectorElementsClickInfo*)vectorElementsClickInfo
{
    // do nothing
}

@end

@implementation RoutePackageManagerListener

- (void)getPackage:(NSString *)package{
    NTPackageStatus* status = [_packageManager getLocalPackageStatus: package version:-1];
    
    if (status == nil) {
        [_packageManager startPackageDownload: package];
    } else if ([status getCurrentAction] == NT_PACKAGE_ACTION_READY) {
        // TODO: report controller that it is downloaded, do not allow routing before!
        NSLog(@"Routing package downloaded");
    }
}

- (void)onPackageListUpdated
{
    NSLog(@"onPackageListUpdated");
    [self getPackage:@"EE-routing"];
    [self getPackage:@"LV-routing"];
    [self getPackage:@"LT-routing"];
}

- (void)onPackageListFailed
{
    NSLog(@"onPackageListFailed");
}

- (void)onPackageUpdated:(NSString*)packageId version:(int)version
{
}

- (void)onPackageCancelled:(NSString*)packageId version:(int)version
{
}

- (void)onPackageFailed:(NSString*)packageId version:(int)version errorType:(enum NTPackageErrorType)errorType
{
    NSLog(@"onPackageFailed");
}

- (void)onPackageStatusChanged:(NSString*)packageId version:(int)version status:(NTPackageStatus*)status
{
    NSLog(@"onPackageStatusChanged progress: %f", [status getProgress]);
}

@end
