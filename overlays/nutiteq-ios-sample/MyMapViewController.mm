#import "MyMapViewController.h"
#import "MyMapEventListener.h"
#import "MyMergedRasterTileDataSource.h"

@interface MyMapViewController ()

@end

@implementation MyMapViewController

- (void)viewDidLoad
{
    //[NTLog setShowDebug:YES];
    //[NTLog setShowInfo:YES];
    
    [super viewDidLoad];
    
    // Set the base projection, that will be used for most MapView, MapEventListener and Options methods
    NTEPSG3857* proj = [[NTEPSG3857 alloc] init];
    [[self getOptions] setBaseProjection:proj];
    
    // Set initial location and other parameters, don't animate
    [self setFocusPos:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.650415 y:59.428773]]  durationSeconds:0];
    [self setZoom:14 durationSeconds:0];
    [self setRotation:0 durationSeconds:0];
    
    // General options
    [[self getOptions] setTileDrawSize:256];
  
#define VECTOR_BACKGROUND 1
  
  if(VECTOR_BACKGROUND){
    // Use modern vector background. Suggested strongly, especially if you rotate and tilt the map
    
    // Load vector tile styleset
    UnsignedCharVector *vectorTileStyleSetData = [NTAssetUtils loadBytes: @"osmbright.zip"];
    NTMBVectorTileStyleSet *vectorTileStyleSet = [[NTMBVectorTileStyleSet alloc] initWithData:vectorTileStyleSetData];
    // Create vector tile decoder using the styleset
    NTMBVectorTileDecoder *vectorTileDecoder = [[NTMBVectorTileDecoder alloc] initWithStyleSet:vectorTileStyleSet];
    
    NTVectorTileDataSource *vectorTileDataSource;

#define ONLINE_VECTOR 1
    
    if(ONLINE_VECTOR){
      
    // Create online vector tile data source, use Nutiteq test account
      vectorTileDataSource = [[NTHTTPVectorTileDataSource alloc] initWithMinZoom:0 maxZoom:14 baseURL:@"http://api.nutiteq.com/v1/nutiteq.mbstreets/{zoom}/{x}/{y}.vt?user_key=15cd9131072d6df68b8a54feda5b0496"];

    }else{
      // file-based offline datasource
      NSString* fullpathVT = [[NSBundle mainBundle] pathForResource:@"budapest_mbvt"
                                                             ofType:@"db"];
      vectorTileDataSource = [[NTMBTilesVectorTileDataSource alloc] initWithMinZoom:0 maxZoom:14 path: fullpathVT];
    }
    // Create vector tile layer, using previously created data source and decoder
    NTVectorTileLayer *vectorTileLayer = [[NTVectorTileLayer alloc] initWithDataSource:vectorTileDataSource decoder:vectorTileDecoder];
    // Add vector tile layer
    [[self getLayers] add:vectorTileLayer];

    
    
  }else{
    // use old-school raster background layer. Use only if vector is not available for your case
    
    // Initialize a OSM raster data source
    NTHTTPRasterTileDataSource* baseRasterTileDataSource = [[NTHTTPRasterTileDataSource alloc] initWithMinZoom:0 maxZoom:24 baseURL:@"http://api.tiles.mapbox.com/v3/nutiteq.map-j6a1wkx0/{zoom}/{x}/{y}.png"];
    // Initialize PSM hillshading raster data source
    NTHTTPRasterTileDataSource* hillsRasterTileDataSource = [[NTHTTPRasterTileDataSource alloc] initWithMinZoom:0 maxZoom:24 baseURL:@"http://toolserver.org/~cmarqu/hill/{zoom}/{x}/{y}.png"];
    // Initialize a custom datasource that will combine those two datasources into one
    MyMergedRasterTileDataSource* mergedRasterTileDataSource = [[MyMergedRasterTileDataSource alloc] initWithDataSource1:baseRasterTileDataSource dataSource2:hillsRasterTileDataSource];
    // Initialize offline raster tile cache with the previous datasource and a sqlite database
    NTPersistentCacheRasterTileDataSource* cachedRasterTileDataSource = [[NTPersistentCacheRasterTileDataSource alloc] initWithDataSource:mergedRasterTileDataSource databasePath:[NTAssetUtils calculateWritablePath:@"cache4.db"]];
    
    // Initialize a raster layer with the previous data source
    NTRasterTileLayer* rasterLayer = [[NTRasterTileLayer alloc] initWithDataSource:cachedRasterTileDataSource];
    //[rasterLayer setPreloading:NO];
    // Add the previous raster layer to the map
    [[self getLayers] add:rasterLayer];
    
  }
  
  
    
    // Initialize an unculled vector data source
    NTUnculledVectorDataSource* vectorDataSource1 = [[NTUnculledVectorDataSource alloc] initWithProjection:proj];
    // Initialize a vector layer with the previous data source
    NTVectorLayer* vectorLayer1 = [[NTVectorLayer alloc] initWithDataSource:vectorDataSource1];
    // Add the previous vector layer to the map
    [[self getLayers] add:vectorLayer1];
    // Set visible zoom range for the vector layer
    [vectorLayer1 setVisibleZoomRange:[[NTMapRange alloc] initWithMin:10 max:24]];
    
    // Create a map event listener
    MyMapEventListener* mapListener = [[MyMapEventListener alloc] init];
    [[self getOptions] setMapEventListener:mapListener];
    mapListener = [[MyMapEventListener alloc] init];
    [[self getOptions] setMapEventListener:mapListener];
    // MapEventListener needs the data source and the layer to display balloons
    // over the clicked vector elements
    [mapListener setMapView:self vectorDataSource:vectorDataSource1 vectorLayer:vectorLayer1];
    
    // Initialize a second vector data source and vector layer.
    // This secondary vector layer will be used for drawing borders for
    // line elements (by drawing the same line twice, with different widths).
    // Drawing order withing a layer is currently undefined.
    // Using multiple layers is the only way to guarantee
    // that point, line and polygon elements are drawn in a specific order.
    NTUnculledVectorDataSource* vectorDataSource2 = [[NTUnculledVectorDataSource alloc] initWithProjection:proj];
    NTVectorLayer* vectorLayer2 = [[NTVectorLayer alloc] initWithDataSource:vectorDataSource2];
    [[self getLayers] add:vectorLayer2];
    [vectorLayer2 setVisibleZoomRange:[[NTMapRange alloc] initWithMin:10 max:24]];
    
    // Add vector elements. All vector elements need a position, which defines the location
    // and a style, which defines how they look. Styles can be created using StyleBuilders.
    
    // First point, create style and position
    NTPointStyleBuilder* pointStyleBuilder = [[NTPointStyleBuilder alloc] init];
    [pointStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFF00FF00]];
    [pointStyleBuilder setSize:16];
    NTMapPos* pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.651488 y:59.423581]];
    // Add to datasource
    NTPoint* point1 = [[NTPoint alloc] initWithPos:pos style:[pointStyleBuilder buildStyle]];
    [point1 setMetaDataElement:@"ClickText" element:@"Point nr 1"];
    [vectorDataSource1 add:point1];
    
    // Second point, create style and position
    pointStyleBuilder = [[NTPointStyleBuilder alloc] init];
    [pointStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFF0000FF]];
    pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.655994 y:59.422716]];
    // Add to datasource
    NTPoint* point2 = [[NTPoint alloc] initWithPos:pos style:[pointStyleBuilder buildStyle]];
    [point2 setMetaDataElement:@"ClickText" element:@"Point nr 2"];
    [vectorDataSource1 add:point2];
    
    // First line, create style and positions
    NTLineStyleBuilder* lineStyleBuilder = [[NTLineStyleBuilder alloc] init];
    [lineStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFFFFFFFF]];
    [lineStyleBuilder setLineJointType:NT_LINE_JOINT_TYPE_ROUND];
    [lineStyleBuilder setStretchFactor:2];
    [lineStyleBuilder setWidth:8];
    MapPosVector* linePoses = [[MapPosVector alloc] init];
    [linePoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.645565 y:59.422074]]];
    [linePoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.643076 y:59.420502]]];
    [linePoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.645351 y:59.419149]]];
    [linePoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.648956 y:59.420393]]];
    [linePoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.650887 y:59.422707]]];
    // Add to datasource
    NTLine* line1 = [[NTLine alloc] initWithGeometry:[[NTLineGeometry alloc] initWithPoses:linePoses] style:[lineStyleBuilder buildStyle]];
    [line1 setMetaDataElement:@"ClickText" element:@"Line nr 1"];
    [vectorDataSource2 add:line1];
    
    // Second line, create style, reuse the same line position
    lineStyleBuilder = [[NTLineStyleBuilder alloc] init];
    [lineStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFFCC0F00]];
    [lineStyleBuilder setWidth:12];
    // Add to datasource
    NTLine* line2 = [[NTLine alloc] initWithGeometry:[[NTLineGeometry alloc] initWithPoses:linePoses] style:[lineStyleBuilder buildStyle]];
    [line2 setMetaDataElement:@"ClickText" element:@"Line nr 2"];
    [vectorDataSource1 add:line2];
    
    // Create polygon style and poses
    NTPolygonStyleBuilder* polygonStyleBuilder = [[NTPolygonStyleBuilder alloc] init];
    [polygonStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFFFF0000]];
    lineStyleBuilder = [[NTLineStyleBuilder alloc] init];
    [lineStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFF000000]];
    [lineStyleBuilder setWidth:1.0f];
    [polygonStyleBuilder setLineStyle:[lineStyleBuilder buildStyle]];
    MapPosVector* polygonPoses = [[MapPosVector alloc] init];
    [polygonPoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.650930 y:59.421659]]];
    [polygonPoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.657453 y:59.416354]]];
    [polygonPoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.661187 y:59.414607]]];
    [polygonPoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.667667 y:59.418123]]];
    [polygonPoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.665736 y:59.421703]]];
    [polygonPoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.661444 y:59.421245]]];
    [polygonPoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.660199 y:59.420677]]];
    [polygonPoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.656552 y:59.420175]]];
    [polygonPoses add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.654010 y:59.421472]]];
    // Create polygon holes poses
    MapPosVectorVector* holes = [[MapPosVectorVector alloc] init];
    [holes add:[[MapPosVector alloc] init]];
    [[holes get:0] add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.658409 y:59.420522]]];
    [[holes get:0] add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.662207 y:59.418896]]];
    [[holes get:0] add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.662207 y:59.417411]]];
    [[holes get:0] add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.659524 y:59.417171]]];
    [[holes get:0] add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.657615 y:59.419834]]];
    [holes add:[[MapPosVector alloc] init]];
    [[holes get:1] add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.665640 y:59.421243]]];
    [[holes get:1] add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.668923 y:59.419463]]];
    [[holes get:1] add:[proj fromWgs84:[[NTMapPos alloc] initWithX:24.662893 y:59.419365]]];
    // Add to datasource
    NTPolygon* polygon = [[NTPolygon alloc] initWithGeometry:[[NTPolygonGeometry alloc] initWithPoses:polygonPoses holes:holes] style:[polygonStyleBuilder buildStyle]];
    [polygon setMetaDataElement:@"ClickText" element:@"Polygon"];
    [vectorDataSource1 add:polygon];
    
    // Load bitmaps for custom markers
    UIImage* markerImage = [UIImage imageNamed:@"marker.png"];
    NTBitmap* markerBitmap = [NTBitmapUtils createBitmapFromUIImage:markerImage];
    
    // Create text style
    NTTextStyleBuilder* textStyleBuilder = [[NTTextStyleBuilder alloc] init];
    [textStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFFFF0000]];
    [textStyleBuilder setOrientationMode:NT_BILLBOARD_ORIENTATION_FACE_CAMERA];
    // This enables higher resolution texts for retina devices  but consumes more memory and is slower
    [textStyleBuilder setScaleWithDPI:false];
    // Add text
    pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.653302 y:59.422269]];
    NTText* text1 = [[NTText alloc] initWithPos:pos
                                          style:[textStyleBuilder buildStyle]
                                           text:@"Face camera"];
    [text1 setMetaDataElement:@"ClickText" element:@"Text nr 1"];
    [vectorDataSource1 add:text1];
    // Add text
    textStyleBuilder = [[NTTextStyleBuilder alloc] init];
    [textStyleBuilder setOrientationMode:NT_BILLBOARD_ORIENTATION_FACE_CAMERA_GROUND];
    pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.633216 y:59.426869]];
    NTText* text2 = [[NTText alloc] initWithPos:pos
                                          style:[textStyleBuilder buildStyle]
                                           text:@"Face camera ground"];
    [text2 setMetaDataElement:@"ClickText" element:@"Text nr 2"];
    [vectorDataSource1 add:text2];
    // Add text
    textStyleBuilder = [[NTTextStyleBuilder alloc] init];
    [textStyleBuilder setFontSize:22];
    [textStyleBuilder setOrientationMode:NT_BILLBOARD_ORIENTATION_GROUND];
    pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.646457 y:59.420839]];
    NTText* text3 = [[NTText alloc] initWithPos:pos
                                          style:[textStyleBuilder buildStyle]
                                           text:@"Ground"];
    [text3 setMetaDataElement:@"ClickText" element:@"Text nr 3"];
    [vectorDataSource1 add:text3];

    
    // Create a marker style, use it for both markers, because they should look the same
    NTMarkerStyleBuilder* markerStyleBuilder = [[NTMarkerStyleBuilder alloc] init];
    [markerStyleBuilder setBitmap:markerBitmap];
    [markerStyleBuilder setSize:30];
    NTMarkerStyle* sharedMarkerStyle = [markerStyleBuilder buildStyle];
    // First marker
    pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.646469 y:59.426939]];
    NTMarker* marker1 = [[NTMarker alloc] initWithPos:pos style:sharedMarkerStyle];
    [marker1 setMetaDataElement:@"ClickText" element:@"Marker nr 1"];
    [vectorDataSource1 add:marker1];
    // Second marker
    pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.666469 y:59.422939]];
    NTMarker* marker2 = [[NTMarker alloc] initWithPos:pos style:sharedMarkerStyle];
    [marker2 setMetaDataElement:@"ClickText" element:@"Marker nr 2"];
    [vectorDataSource1 add:marker2];

    // Load bitmaps to show on the popups
    UIImage* infoImage = [UIImage imageNamed:@"info.png"];
    UIImage* arrowImage = [UIImage imageNamed:@"arrow.png"];
    
    // First popup, create style and position
    NTBalloonPopupStyleBuilder* balloonPopupStyleBuilder = [[NTBalloonPopupStyleBuilder alloc] init];
    [balloonPopupStyleBuilder setCornerRadius:20];
    [balloonPopupStyleBuilder setLeftMargins:[[NTBalloonPopupMargins alloc] initWithLeft:6 top:6 right:6 bottom:6]];
    [balloonPopupStyleBuilder setLeftImage:infoImage];
    [balloonPopupStyleBuilder setRightImage:arrowImage];
    [balloonPopupStyleBuilder setRightMargins:[[NTBalloonPopupMargins alloc] initWithLeft:2 top:6 right:12 bottom:6]];
    [balloonPopupStyleBuilder setPlacementPriority:1];
    pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.655662 y:59.425521]];
    // Add to datasource
    NTBalloonPopup* popup1 = [[NTBalloonPopup alloc] initWithPos:pos
                                                           style:[balloonPopupStyleBuilder buildStyle]
                                                           title:@"Popup with pos"
                                                            desc:@"Images, round"];
    [popup1 setMetaDataElement:@"ClickText" element:@"Popupception nr 1"];
    [vectorDataSource1 add:popup1];
    
    // Second popup, but instead of giving it a position attach it to a marker
    balloonPopupStyleBuilder = [[NTBalloonPopupStyleBuilder alloc] init];
    [balloonPopupStyleBuilder setColor:[[NTColor alloc] initWithColor:0xFF000000]];
    [balloonPopupStyleBuilder setCornerRadius:0];
    [balloonPopupStyleBuilder setTitleColor:[[NTColor alloc] initWithColor:0xFFFFFFFF]];
    [balloonPopupStyleBuilder setTitleFontName:@"HelveticaNeue-Medium"];
    [balloonPopupStyleBuilder setDescriptionColor:[[NTColor alloc] initWithColor:0xFFFFFFFF]];
    [balloonPopupStyleBuilder setDescriptionFontName:@"HelveticaNeue-Medium"];
    [balloonPopupStyleBuilder setStrokeColor:[[NTColor alloc] initWithColor:0xFF00B483]];
    [balloonPopupStyleBuilder setStrokeWidth:0];
    [balloonPopupStyleBuilder setPlacementPriority:1];
    // Add to datasource
    NTBalloonPopup* popup2 = [[NTBalloonPopup alloc] initWithBaseBillboard:marker1
                                                                     style:[balloonPopupStyleBuilder buildStyle]
                                                                     title:@"Popup attached to marker"
                                                                      desc:@"Black, rectangle"];
    [popup2 setMetaDataElement:@"ClickText" element:@"Popupception nr 2"];
    [vectorDataSource1 add:popup2];
    
    // Third popup, create a style and position
    balloonPopupStyleBuilder = [[NTBalloonPopupStyleBuilder alloc] init];
    [balloonPopupStyleBuilder setDescriptionWrap:NO];
    [balloonPopupStyleBuilder setPlacementPriority:1];
    pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.658662 y:59.432521]];
    // Add to datasource
    NTBalloonPopup* popup3 = [[NTBalloonPopup alloc] initWithPos:pos
                                                           style:[balloonPopupStyleBuilder buildStyle]
                                                           title:@"This title will be wrapped if there's not enough space on the screen."
                                                            desc:@"Description is set to be truncated with three dots, unless the screen is really really big."];
    [popup3 setMetaDataElement:@"ClickText" element:@"Popupception nr 3"];
    [vectorDataSource1 add:popup3 ];
    
    // Add a single 3D model
    UnsignedCharVector* modelData = [NTAssetUtils loadBytes:@"milktruck.nml"];
    pos = [proj fromWgs84:[[NTMapPos alloc] initWithX:24.646469 y:59.424939]];
    NTNMLModel* model = [[NTNMLModel alloc] initWithPos:pos sourceModelData:modelData];
    [model setMetaDataElement:@"ClickText" element:@"Single model"];
    [model setScale:20];
    [vectorDataSource1 add:model];

    //Add a 3D model database layer
    NSString* fullpath = [[NSBundle mainBundle] pathForResource:@"saku_ios_4bpp" ofType:@"nmldb"];
    NTNMLModelLODTreeSqliteDataSource* nmlDataSource = [[NTNMLModelLODTreeSqliteDataSource alloc] initWithProjection:proj fileName:fullpath];
    NTNMLModelLODTreeLayer* nmlLayer = [[NTNMLModelLODTreeLayer alloc] initWithDataSource:nmlDataSource];
    [nmlLayer setVisibleZoomRange:[[NTMapRange alloc] initWithMin:12 max:25]];
    [[self getLayers] add:nmlLayer];
 }

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
