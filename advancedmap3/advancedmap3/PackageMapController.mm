#import "PackageMapController.h"


@implementation PackageMapController
@synthesize dataSource = _dataSource;

- (NTTileDataSource*)createTileDataSource
{
	return _dataSource;
}

- (void)viewDidLoad
{
	[super viewDidLoad];
  [self setZoom:2.0f durationSeconds:0.2f];
  [self setTilt:90.0f durationSeconds:0.2f];
}

@end
