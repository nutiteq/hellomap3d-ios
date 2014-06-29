#import <Nuti/Nuti.h>

@interface  MyMergedRasterTileDataSource : NTRasterTileDataSource

-(id)initWithDataSource1: (NTRasterTileDataSource*)dataSource1 dataSource2: (NTRasterTileDataSource*)dataSource2;

-(NTRasterTileBitmap*)loadTile: (NTMapTile*)tile;

@end