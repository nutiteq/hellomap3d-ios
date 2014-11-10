#import <Nuti/Nuti.h>
#import "MyMergedRasterTileDataSource.h"

@interface CustomRasterDataSourceSampleController : NTMapViewController

@end

@implementation CustomRasterDataSourceSampleController

- (void)viewDidLoad
{
	[super viewDidLoad];
	
	// Set the base projection, that will be used for most MapView, MapEventListener and Options methods
	NTEPSG3857* proj = [[NTEPSG3857 alloc] init];
	[[self getOptions] setBaseProjection:proj];

	// General options
	[[self getOptions] setTileDrawSize:256];
	
	// Set initial location and other parameters, don't animate
	[self setFocusPos:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.650415 y:59.428773]]  durationSeconds:0];
	[self setZoom:5 durationSeconds:0];
	[self setRotation:0 durationSeconds:0];
	
	// Initialize a OSM raster data source
	NTHTTPTileDataSource* baseRasterTileDataSource = [[NTHTTPTileDataSource alloc] initWithMinZoom:0 maxZoom:24 baseURL:@"http://api.tiles.mapbox.com/v3/nutiteq.map-j6a1wkx0/{zoom}/{x}/{y}.png"];
	// Initialize PSM hillshading raster data source
	NTHTTPTileDataSource* hillsRasterTileDataSource = [[NTHTTPTileDataSource alloc] initWithMinZoom:0 maxZoom:24 baseURL:@"http://tiles.wmflabs.org/hillshading/{zoom}/{x}/{y}.png"];
	// Initialize a custom datasource that will combine those two datasources into one
	MyMergedRasterTileDataSource* mergedRasterTileDataSource = [[MyMergedRasterTileDataSource alloc] initWithDataSource1:baseRasterTileDataSource dataSource2:hillsRasterTileDataSource];
	// Initialize offline raster tile cache with the previous datasource and a sqlite database
	NTPersistentCacheTileDataSource* cachedRasterTileDataSource = [[NTPersistentCacheTileDataSource alloc] initWithDataSource:mergedRasterTileDataSource databasePath:[NTAssetUtils calculateWritablePath:@"cache4.db"]];
		
	// Initialize a raster layer with the previous data source
	NTRasterTileLayer* rasterLayer = [[NTRasterTileLayer alloc] initWithDataSource:cachedRasterTileDataSource];
	//[rasterLayer setPreloading:NO];
	// Add the previous raster layer to the map
	[[self getLayers] add:rasterLayer];
}

- (void)didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
}

@end
