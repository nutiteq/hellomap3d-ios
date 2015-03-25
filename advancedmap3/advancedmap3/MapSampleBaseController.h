#import <Nuti/Nuti.h>
#import <GLKit/GLKit.h>

/*
 * Base controller for map samples. Includes simple lifecycle management.
 */
@interface MapSampleBaseController : GLKViewController

@property (nonatomic,strong) NTMapView* mapView;

@end
