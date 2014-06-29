#import "MyMapEventListener.h"

@interface  MyMapEventListener() {
}

@property (strong, nonatomic) NTMapViewController* mapView;

@property (strong, nonatomic) NTUnculledVectorDataSource* vectorDataSource;
@property (strong, nonatomic) NTVectorLayer* vectorLayer;

@property (strong, nonatomic) NTBalloonPopup* oldClickLabel;

@end;

@implementation MyMapEventListener

-(void)setMapView:(NTMapViewController*)mapView vectorDataSource:(NTUnculledVectorDataSource*)vectorDataSource vectorLayer:(NTVectorLayer*)vectorLayer
{
    _mapView = mapView;
    _vectorDataSource = vectorDataSource;
    _vectorLayer = vectorLayer;
}

-(void)onMapMoved
{
}

-(void)onMapClicked:(NTMapClickInfo*)mapClickInfo
{
    NSLog(@"Map click!");
    // Remove old click label
    if (_oldClickLabel)
    {
        [_vectorDataSource remove:_oldClickLabel];
        _oldClickLabel = nil;
    }
    
    NTBalloonPopup* clickPopup = [[NTBalloonPopup alloc] init];
    NTBalloonPopupStyleBuilder* styleBuilder = [[NTBalloonPopupStyleBuilder alloc] init];
    // Make sure this label is shown on top all other labels
    [styleBuilder setPlacementPriority:10];
    
    // Check the type of the click
    NSString* clickMsg;
    if ([mapClickInfo getClickType] == NT_CLICK_TYPE_SINGLE)
    {
        clickMsg = @"Single map click!";
        return;
    }
    else if ([mapClickInfo getClickType] == NT_CLICK_TYPE_LONG)
    {
        clickMsg = @"Long map click!";
    }
    else if ([mapClickInfo getClickType] == NT_CLICK_TYPE_DOUBLE)
    {
        clickMsg = @"Double map click!";
    }
    else if ([mapClickInfo getClickType] == NT_CLICK_TYPE_DUAL)
    {
        clickMsg = @"Dual map click!";
    }
    
    NTMapPos* clickPos = [mapClickInfo getClickPos];
    NTMapPos* wgs84Clickpos = [[[_mapView getOptions] getBaseProjection] toWgs84:clickPos];

    clickPopup = [[NTBalloonPopup alloc] initWithPos:[mapClickInfo getClickPos]
                                               style:[styleBuilder buildStyle]
                                               title:clickMsg
                                                desc:[NSString stringWithFormat:@"%f, %f", [wgs84Clickpos getY], [wgs84Clickpos getX]]];
    [_vectorDataSource add:clickPopup];
    _oldClickLabel = clickPopup;

}

-(void)onVectorElementClicked:(NTVectorElementsClickInfo*)vectorElementsClickInfo
{
    NSLog(@"Vector element click!");
    // Remove old click label
    if (_oldClickLabel)
    {
        [_vectorDataSource remove:_oldClickLabel];
        _oldClickLabel = nil;
    }
    
    // Multiple vector elements can be clicked at the same time, we only care about the one
    // closest to the camera
    NTVectorElementClickInfo* clickInfo = [[vectorElementsClickInfo getVectorElementClickInfos] get:0];
    
    
    NTBalloonPopup* clickPopup = [[NTBalloonPopup alloc] init];
    NTBalloonPopupStyleBuilder* styleBuilder = [[NTBalloonPopupStyleBuilder alloc] init];
    // Configure style
    [styleBuilder setLeftMargins:[[NTBalloonPopupMargins alloc] initWithLeft:0 top:0 right:0 bottom:0]];
    [styleBuilder setTitleMargins:[[NTBalloonPopupMargins alloc] initWithLeft:6 top:3 right:6 bottom:3]];
    // Make sure this label is shown on top all other labels
    [styleBuilder setPlacementPriority:10];
    
    // Check the type of vector element
    NTVectorElement* vectorElement = [clickInfo getVectorElement];
    if ([vectorElement isKindOfClass:[NTBillboard class]])
    {
        NTBillboard* billboard = (NTBillboard*)vectorElement;
        // If the element is billboard, attach the click label to the billboard element
        clickPopup = [[NTBalloonPopup alloc] initWithBaseBillboard:billboard
                                                             style:[styleBuilder buildStyle]
                                                             title:[billboard getMetaDataElement:@"ClickText"]
                                                              desc:@""];
    }
    else
    {
        // for lines and polygons set label to click location
        clickPopup = [[NTBalloonPopup alloc] initWithPos:[clickInfo getElementClickPos]
                                                   style:[styleBuilder buildStyle]
                                                   title:[vectorElement getMetaDataElement:@"ClickText"]
                                                    desc:@""];
    }
    [_vectorDataSource add:clickPopup];
    _oldClickLabel = clickPopup;
}

@end
