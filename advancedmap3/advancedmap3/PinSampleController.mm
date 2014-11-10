#import "VectorMapSampleBaseController.h"

@interface PinSampleController : VectorMapSampleBaseController

@end

@implementation PinSampleController

- (void)viewDidLoad
{
	[super viewDidLoad];
	
	// Initialize a local vector data source
	NTProjection* proj = [[self getOptions] getBaseProjection];
	NTLocalVectorDataSource* vectorDataSource = [[NTLocalVectorDataSource alloc] initWithProjection:proj];
	// Initialize a vector layer with the previous data source
	NTVectorLayer* vectorLayer = [[NTVectorLayer alloc] initWithDataSource:vectorDataSource];
	// Add the previous vector layer to the map
	[[self getLayers] add:vectorLayer];
		
	// Load bitmaps for custom markers
	UIImage* markerImage = [UIImage imageNamed:@"marker.png"];
	NTBitmap* markerBitmap = [NTBitmapUtils createBitmapFromUIImage:markerImage];
	
	// Create a marker style, use it for both markers, because they should look the same
	NTMarkerStyleBuilder* markerStyleBuilder = [[NTMarkerStyleBuilder alloc] init];
	[markerStyleBuilder setBitmap:markerBitmap];
	[markerStyleBuilder setSize:30];
	NTMarkerStyle* sharedMarkerStyle = [markerStyleBuilder buildStyle];

	// First marker
	NTMapPos* pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.646469 y:59.426939]];
	NTMarker* marker = [[NTMarker alloc] initWithPos:pos style:sharedMarkerStyle];
	[marker setMetaDataElement:@"ClickText" element:@"Marker nr 1"];
	[vectorDataSource add:marker];
}

@end
