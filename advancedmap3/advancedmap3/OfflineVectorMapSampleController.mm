#import "VectorMapSampleBaseController.h"

@interface OfflineVectorMapSampleController : VectorMapSampleBaseController

@end

@implementation OfflineVectorMapSampleController

- (void)viewDidLoad
{
	[super viewDidLoad];
	
	// Get the base projection set in the base class
	NTProjection* proj = [[self getOptions] getBaseProjection];
	
	// Zoom to Berlin
	[self setFocusPos:[proj fromWgs84:[[NTMapPos alloc] initWithX:13.38933 y:52.51704]]  durationSeconds:0];
	[self setZoom:13 durationSeconds:0];
	
	// file-based local offline datasource
	NSString* fullpathVT = [[NSBundle mainBundle] pathForResource:@"berlin_ntvt" ofType:@"mbtiles"];
	NTTileDataSource* vectorTileDataSource = [[NTMBTilesTileDataSource alloc] initWithMinZoom:0 maxZoom:12 path:fullpathVT scheme:MBTILES_SCHEME_XYZ];
	
	// Create vector tile layer, using previously created data source and decoder
	[[self getLayers] remove: self.baseLayer];
	self.baseLayer = [[NTVectorTileLayer alloc] initWithDataSource:vectorTileDataSource decoder:self.vectorTileDecoder];
	[[self getLayers] add:self.baseLayer];		
}

@end
