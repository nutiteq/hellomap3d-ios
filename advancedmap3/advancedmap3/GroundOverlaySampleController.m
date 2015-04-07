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
    NTBitmap* overlayBitmap = [[NTBitmap alloc] initWithCompressedData:[NTAssetUtils loadBytes:@"jefferson-building-ground-floor.jpg"] pow2Padding:NO];
    
    // Create two vector containing geographical positions and corresponding raster image pixel coordinates
    NTMapPos* pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:-77.004590 y:38.888702]];
    double sizeNS = 110, sizeWE = 100;

    NTMapPosVector* mapPoses = [[NTMapPosVector alloc] init];
    [mapPoses add:[[NTMapPos alloc] initWithX:[pos getX]-sizeWE y:[pos getY]+sizeNS]];
    [mapPoses add:[[NTMapPos alloc] initWithX:[pos getX]+sizeWE y:[pos getY]+sizeNS]];
    [mapPoses add:[[NTMapPos alloc] initWithX:[pos getX]+sizeWE y:[pos getY]-sizeNS]];
    [mapPoses add:[[NTMapPos alloc] initWithX:[pos getX]-sizeWE y:[pos getY]-sizeNS]];
    
    NTScreenPosVector* bitmapPoses = [[NTScreenPosVector alloc] init];
    [bitmapPoses add:[[NTScreenPos alloc] initWithX:0 y:0]];
    [bitmapPoses add:[[NTScreenPos alloc] initWithX:0 y:[overlayBitmap getOrigHeight]]];
    [bitmapPoses add:[[NTScreenPos alloc] initWithX:[overlayBitmap getOrigWidth] y:[overlayBitmap getOrigHeight]]];
    [bitmapPoses add:[[NTScreenPos alloc] initWithX:[overlayBitmap getOrigWidth] y:0]];
    
    // Create bitmap overlay raster tile data source
    NTBitmapOverlayRasterTileDataSource* rasterDataSource = [[NTBitmapOverlayRasterTileDataSource alloc] initWithMinZoom:0 maxZoom:20 bitmap:overlayBitmap projection:proj mapPoses:mapPoses bitmapPoses:bitmapPoses];
    NTRasterTileLayer* rasterLayer = [[NTRasterTileLayer alloc] initWithDataSource:rasterDataSource];
    [[self.mapView getLayers] add:rasterLayer];
    
    // Apply zoom level bias to the raster layer.
    // By default, bitmaps are upsampled on high-DPI screens.
    // We will correct this by applying appropriate bias
    float zoomLevelBias = log([[self.mapView getOptions] getDPI] / 160.0f) / log(2);
    [rasterLayer setZoomLevelBias:zoomLevelBias * 0.75f];
    [rasterLayer setTileSubstitutionPolicy:NT_TILE_SUBSTITUTION_POLICY_VISIBLE];
    
    [self.mapView setFocusPos:pos durationSeconds:0];
    [self.mapView setZoom:15.5f durationSeconds:0];
}

@end
