#import <Nuti/Nuti.h>

@interface  MyMapEventListener : NTMapEventListener

-(void)setMapView:(NTMapViewController*)mapView vectorDataSource:(NTLocalVectorDataSource*)vectorDataSource vectorLayer:(NTVectorLayer*)vectorLayer;
-(void)onMapMoved;
-(void)onMapClicked:(NTMapClickInfo*)mapClickInfo;
-(void)onVectorElementClicked:(NTVectorElementsClickInfo*)vectorElementsClickInfo;

@end