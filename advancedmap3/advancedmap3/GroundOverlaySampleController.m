#import "VectorMapSampleBaseController.h"

/*
 * A sample demonstrating how to add ground level raster overlay. This samples
 * adds additional raster layer on top of base layer, using NTBitmapOverlayRasterTileDataSource.
 * Note: for really big overlays (containing 10000 pixels or more), Nutiteq SDK provides
 * GDAL-based raster tile data source. This data source is not part of the standard SDK, it
 * is an extra feature provided using GIS-extensions package.
 */
@interface GroundOverlaySampleController : VectorMapSampleBaseController

@end

@implementation GroundOverlaySampleController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    NTProjection* proj = [[self.mapView getOptions] getBaseProjection];

    // Load ground overlay bitmap
    UIImage* overlayImage = [UIImage imageNamed:@"jefferson-building-ground-floor.jpg"];
    NTBitmap* overlayBitmap = [NTBitmapUtils createBitmapFromUIImage:overlayImage pow2Padding:NO];
    
    // Create two vector containing geographical positions and corresponding raster image pixel coordinates
    NTMapPos* pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:-77.004590 y:38.888702]];
    double sizeNS = 110, sizeWE = 100;

    NTMapPosVector* mapPoses = [[NTMapPosVector alloc] init];
    [mapPoses add:[[NTMapPos alloc] initWithX:[pos getX]-sizeWE y:[pos getY]+sizeNS]];
    [mapPoses add:[[NTMapPos alloc] initWithX:[pos getX]+sizeWE y:[pos getY]+sizeNS]];
    [mapPoses add:[[NTMapPos alloc] initWithX:[pos getX]+sizeWE y:[pos getY]-sizeNS]];
    [mapPoses add:[[NTMapPos alloc] initWithX:[pos getX]-sizeWE y:[pos getY]-sizeNS]];
    
    NTScreenPosVector* screenPoses = [[NTScreenPosVector alloc] init];
    [screenPoses add:[[NTScreenPos alloc] initWithX:0 y:0]];
    [screenPoses add:[[NTScreenPos alloc] initWithX:0 y:[overlayBitmap getHeight]]];
    [screenPoses add:[[NTScreenPos alloc] initWithX:[overlayBitmap getWidth] y:[overlayBitmap getHeight]]];
    [screenPoses add:[[NTScreenPos alloc] initWithX:[overlayBitmap getWidth] y:0]];
    
    NTBitmapOverlayRasterTileDataSource* rasterDataSource = [[NTBitmapOverlayRasterTileDataSource alloc] initWithMinZoom:0 maxZoom:24 bitmap:overlayBitmap projection:proj mapPoses:mapPoses bitmapPoses:screenPoses];
    NTRasterTileLayer* rasterLayer = [[NTRasterTileLayer alloc] initWithDataSource:rasterDataSource];
    [rasterLayer setTileSubstitutionPolicy:NT_TILE_SUBSTITUTION_POLICY_VISIBLE];
    [rasterLayer setZoomLevelBias:0.75f];
    [[self.mapView getLayers] add:rasterLayer];
    
    [self.mapView setFocusPos:pos durationSeconds:0];
    [self.mapView setZoom:15.5f durationSeconds:0];
}

@end
