#import "VectorMapSampleBaseController.h"

/*
 * A sample that uses bundled asset for offline base map.
 * As MBTilesDataSource can be used only with files residing in file system,
 * the assets needs to be copied first to the SDCard.
 */
@interface OfflineVectorMapSampleController : VectorMapSampleBaseController

@end

@implementation OfflineVectorMapSampleController

- (NTTileDataSource*)createTileDataSource
{
	// file-based local offline datasource
	NSString* fullpathVT = [[NSBundle mainBundle] pathForResource:@"berlin_ntvt" ofType:@"mbtiles"];
	NTTileDataSource* vectorTileDataSource = [[NTMBTilesTileDataSource alloc] initWithMinZoom:0 maxZoom:12 path:fullpathVT scheme:MBTILES_SCHEME_XYZ];
	return vectorTileDataSource;
}

- (void)viewDidLoad
{
	[super viewDidLoad];
	
	// Get the base projection set in the base class
	NTProjection* proj = [[self getOptions] getBaseProjection];
	
	// Zoom to Berlin
	[self setFocusPos:[proj fromWgs84:[[NTMapPos alloc] initWithX:13.38933 y:52.51704]]  durationSeconds:0];
	[self setZoom:13 durationSeconds:0];
}

@end
