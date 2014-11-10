#import "MyMapViewController.h"

@interface MyMapViewController ()

@end

@implementation MyMapViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Set the base projection
	NTEPSG3857* proj = [[NTEPSG3857 alloc] init];
    [[self getOptions] setBaseProjection:proj];
    
	// General options
	[[self getOptions] setTileDrawSize:256];
	
    // Set initial location and other parameters, don't animate
    [self setFocusPos:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.650415 y:59.428773]]  durationSeconds:0];
    [self setZoom:14 durationSeconds:0];
    [self setRotation:0 durationSeconds:0];
    
	// Create online vector tile layer, connect to with demo key and use style asset embedded in the project
	NTVectorTileLayer* vectorTileLayer = [[NTNutiteqOnlineVectorTileLayer alloc] initWithApiKey: @"15cd9131072d6df68b8a54feda5b0496" styleAssetName: @"osmbright_en.zip"];

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
	NTMapPos* pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.646469 y:59.426939]];
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
