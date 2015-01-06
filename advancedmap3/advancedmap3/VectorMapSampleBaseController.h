#import "MapSampleBaseController.h"

@interface VectorMapSampleBaseController : MapSampleBaseController

- (NSDictionary*)languages;
- (NSDictionary*)styles;
- (void)updateBaseLayer;
- (NTTileDataSource*)createTileDataSource;

@property NSString* vectorStyleName;
@property NSString* vectorStyleLanguage;

@property NTVectorTileLayer* baseLayer;
@property NTMBVectorTileDecoder* vectorTileDecoder;

@end
