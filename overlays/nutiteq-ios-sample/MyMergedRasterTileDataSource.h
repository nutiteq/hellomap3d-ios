#import <Nuti/Nuti.h>

@interface  MyMergedRasterTileDataSource : NTTileDataSource

-(id)initWithDataSource1: (NTTileDataSource*)dataSource1 dataSource2: (NTTileDataSource*)dataSource2;

-(NTRasterTileBitmap*)loadTile: (NTMapTile*)tile;

@end