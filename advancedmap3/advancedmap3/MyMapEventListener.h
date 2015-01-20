#import <Nuti/Nuti.h>

/*
 * A custom map event listener that displays information about map events and creates pop-ups.
 */
@interface  MyMapEventListener : NTMapEventListener

-(void)setMapView:(NTMapViewController*)mapView vectorDataSource:(NTLocalVectorDataSource*)vectorDataSource;
-(void)onMapMoved;
-(void)onMapClicked:(NTMapClickInfo*)mapClickInfo;
-(void)onVectorElementClicked:(NTVectorElementsClickInfo*)vectorElementsClickInfo;

@end