#import "VectorMapSampleBaseController.h"

/*
 * A sample that uses bundled asset for offline base map.
 * As MBTilesDataSource can be used only with files residing in file system,
 * the assets needs to be copied first to the SDCard.
 */
@interface PackageMapController : VectorMapSampleBaseController
@property (nonatomic,strong) NTTileDataSource *dataSource;

@end
