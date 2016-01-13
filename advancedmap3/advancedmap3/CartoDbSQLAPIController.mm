#import "VectorMapSampleBaseController.h"
#import "MyMapEventListener.h"
#import "CartoDbSqlDataSource.h"


@interface CartoDbSQLAPIController : VectorMapSampleBaseController

@end

@implementation CartoDbSQLAPIController

-(void)viewDidLoad
{
    [super viewDidLoad];
    
    // Initialize a local vector data source
    NTProjection* proj = [[self.mapView getOptions] getBaseProjection];
    
    // define style
    
    NTPointStyleBuilder* pointStyleBuilder = [[NTPointStyleBuilder alloc] init];
    [pointStyleBuilder setColor:[[NTColor alloc] initWithColor: 0x80f1e8a1]];
    [pointStyleBuilder setSize: 5.0f];
    
    // Option: use cartoCSS to style the objects
    //        NTPointStyleBuilder *pointStyleBuilder = [NTCartoCSSParser createPointStyleBuilder:@""];
    
    // TODO: show osm_eur POIs with this
    
    // note that in URL the spatial condition is !bbox!
    // naive query
//    CartoDbSqlDataSource* vectorDataSource = [[CartoDbSqlDataSource alloc] initWithServer: @"http://54.88.19.221/user/demo-admin/api/v2/sql" query:@"SELECT the_geom_webmercatoras the_geom, * from card_agg WHERE !bbox! limit 50000" style:[pointStyleBuilder buildStyle] proj:proj];
    // from cdb web app
    CartoDbSqlDataSource* vectorDataSource = [[CartoDbSqlDataSource alloc] initWithServer: @"http://54.88.19.221/user/demo-admin/api/v2/sql" query:@"select * from (WITH a as (select zoom('!scale_denominator!') as current_zoom) SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_0_card_2, a where current_zoom = 0 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_1_card_2, a where current_zoom = 1 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_2_card_2, a where current_zoom = 2 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_3_card_2, a where current_zoom = 3 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_4_card_2, a where current_zoom = 4 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_5_card_2, a where current_zoom = 5 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_6_card_2, a where current_zoom = 6 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_7_card_2, a where current_zoom = 7 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_8_card_2, a where current_zoom = 8 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_9_card_2, a where current_zoom = 9 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_10_card_2, a where current_zoom = 10 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_11_card_2, a where current_zoom = 11 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_12_card_2, a where current_zoom = 12 UNION SELECT 0 as cartodb_id, null as cat,the_geom_webmercator,c from ov_13_card_2, a where current_zoom = 13) as DMY WHERE !bbox! limit 50000" style:[pointStyleBuilder buildStyle] proj:proj];
    
    // Initialize a vector layer with the previous data source
    
    NTVectorLayer* vectorLayer = [[NTVectorLayer
                                            alloc] initWithDataSource:vectorDataSource]
                                           ;
    [vectorLayer setVisibleZoomRange:[[NTMapRange alloc] initWithMin:0 max:13.9]];
    
    // Add the previous vector layer to the map
    [[self.mapView getLayers] add:vectorLayer];
    
    // from cdb web app
    CartoDbSqlDataSource* vectorDataSource2 = [[CartoDbSqlDataSource alloc] initWithServer: @"http://54.88.19.221/user/demo-admin/api/v2/sql" query: @"SELECT * FROM (WITH a AS (SELECT zoom('!scale_denominator!') as current_zoom) SELECT cartodb_id, cat,the_geom_webmercator,1 AS c FROM card_agg_2, a WHERE current_zoom >= 14) AS dmy WHERE !bbox! limit 50000" style:[pointStyleBuilder buildStyle] proj:proj];
    
    // Initialize a vector layer with the previous data source
    NTVectorLayer* vectorLayer2 = [[NTVectorLayer
                                   alloc] initWithDataSource:vectorDataSource2]
    ;
    [vectorLayer2 setVisibleZoomRange:[[NTMapRange alloc] initWithMin:14 max:23]];
    
    // Add the previous vector layer to the map
    [[self.mapView getLayers] add:vectorLayer2];
    
    [self.mapView setZoom:1 durationSeconds:0];
    
    // Create a map event listener
    MyMapEventListener* mapListener = [[MyMapEventListener alloc] init];
    
    // MapEventListener needs another in-memory data source and the layer to display balloons
    NTLocalVectorDataSource* clickDataSource = [[NTLocalVectorDataSource alloc] initWithProjection:proj];
    NTVectorLayer* vectorLayer1 = [[NTVectorLayer alloc] initWithDataSource:clickDataSource];
    // Add the previous vector layer to the map
    [[self.mapView getLayers] add:vectorLayer1];
    
    [mapListener setMapView:self.mapView vectorDataSource:clickDataSource];
    
    [self.mapView setMapEventListener:mapListener];
    
}

-(void)viewWillDisappear:(BOOL)animated
{
    // Check if the view is closing
    if ([self.navigationController.viewControllers indexOfObject:self] == NSNotFound) {
        [self.mapView setMapEventListener:nil];
    }
    
    [super viewWillDisappear:animated];
}
/*
- (NTTileDataSource*)createTileDataSource
{
    // file-based local offline datasource
    NSString* fullpathVT = [[NSBundle mainBundle] pathForResource:@"rome_ntvt" ofType:@"mbtiles"];
    NTTileDataSource* vectorTileDataSource = [[NTMBTilesTileDataSource alloc] initWithMinZoom:0 maxZoom:14 path:fullpathVT];
    return vectorTileDataSource;
}
*/
@end

