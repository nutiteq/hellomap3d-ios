#import "MyMapViewController.h"

@interface MyMapViewController ()

@end

@implementation MyMapViewController

- (void)viewDidLoad
{
	// The initial step: register your license. This must be done before using MapView and before calling [super viewDidLoad]!
	// You can get your free/commercial license from: http://developer.nutiteq.com
	// The license string used here is intended only for Nutiteq demos and WILL NOT WORK with other apps!
	[NTMapViewController RegisterLicense:@"XTUN3Q0ZBd2NtcmFxbUJtT1h4QnlIZ2F2ZXR0Mi9TY2JBaFJoZDNtTjUvSjJLay9aNUdSVjdnMnJwVXduQnc9PQoKcHJvZHVjdHM9c2RrLWlvcy0zLiosc2RrLWFuZHJvaWQtMy4qCnBhY2thZ2VOYW1lPWNvbS5udXRpdGVxLioKYnVuZGxlSWRlbnRpZmllcj1jb20ubnV0aXRlcS4qCndhdGVybWFyaz1ldmFsdWF0aW9uCnVzZXJLZXk9MTVjZDkxMzEwNzJkNmRmNjhiOGE1NGZlZGE1YjA0OTYK"];
    
	[super viewDidLoad];
	
	// Set the base projection, that will be used for most MapView, MapEventListener and Options methods
	NTEPSG3857* proj = [[NTEPSG3857 alloc] init];
    [[self getOptions] setBaseProjection:proj]; // EPSG3857 is actually the default base projection, so this is actually not needed
    
	// General options
	[[self getOptions] setRotatable:YES]; // make map rotatable (this is actually the default)
	[[self getOptions] setTileThreadPoolSize:2]; // use 2 threads to download tiles
	
    // Set initial location and other parameters, don't animate
    [self setFocusPos:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.650415 y:59.428773]]  durationSeconds:0];
    [self setZoom:14 durationSeconds:0];
    [self setRotation:0 durationSeconds:0];
    
	// Create online vector tile layer, use style asset embedded in the project
	NTVectorTileLayer* vectorTileLayer = [[NTNutiteqOnlineVectorTileLayer alloc] initWithStyleAssetName:@"osmbright.zip"];

	// Add vector tile layer
    [[self getLayers] add:vectorTileLayer];

	// Load bitmaps for custom markers
	UIImage* markerImage = [UIImage imageNamed:@"marker.png"];
	NTBitmap* markerBitmap = [NTBitmapUtils createBitmapFromUIImage:markerImage];
	
	// Create a marker style, use it for both markers, because they should look the same
	NTMarkerStyleBuilder* markerStyleBuilder = [[NTMarkerStyleBuilder alloc] init];
	[markerStyleBuilder setBitmap:markerBitmap];
	[markerStyleBuilder setSize:30];
	NTMarkerStyle* sharedMarkerStyle = [markerStyleBuilder buildStyle];
	
	// Initialize a local vector data source
    NTLocalVectorDataSource* vectorDataSource = [[NTLocalVectorDataSource alloc] initWithProjection:proj];

	// Create marker, add it to the data source
	NTMapPos* pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.646469 y:59.426939]]; // Tallinn
	NTMarker* marker = [[NTMarker alloc] initWithPos:pos style:sharedMarkerStyle];
	[vectorDataSource add:marker];

	// Initialize a vector layer with the previous data source
    NTVectorLayer* vectorLayer = [[NTVectorLayer alloc] initWithDataSource:vectorDataSource];

	// Add the previous vector layer to the map
    [[self getLayers] add:vectorLayer];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
