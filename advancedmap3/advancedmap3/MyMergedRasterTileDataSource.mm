#import "MyMergedRasterTileDataSource.h"

@interface  MyMergedRasterTileDataSource() {
}

@property (strong, nonatomic) NTTileDataSource* dataSource1;
@property (strong, nonatomic) NTTileDataSource* dataSource2;

@end;

@implementation MyMergedRasterTileDataSource

-(id)initWithDataSource1: (NTTileDataSource*)dataSource1 dataSource2: (NTTileDataSource*)dataSource2
{
    self = [super initWithMinZoom:MIN([dataSource1 getMinZoom], [dataSource2 getMinZoom])
                          maxZoom:MAX([dataSource1 getMaxZoom], [dataSource2 getMaxZoom])];
    if (self != nil)
    {
        _dataSource1 = dataSource1;
        _dataSource2 = dataSource2;
    }
    return self;
}

-(NTTileData*)loadTile: (NTMapTile*)tile
{
    NTTileData* tileData1 = [_dataSource1 loadTile:tile];
    NTTileData* tileData2 = [_dataSource2 loadTile:tile];

    if (!tileData1) {
        return tileData2;
    }
    
    if (!tileData2) {
        return tileData1;
    }
  
    // Create bitmaps

    NTBitmap * tileBitmap1 = [[NTBitmap alloc] initWithCompressedData: tileData1.getData pow2Padding: NO];
    NTBitmap * tileBitmap2 = [[NTBitmap alloc] initWithCompressedData: tileData2.getData pow2Padding: NO];
  
    // Combine the bitmaps
    CGImageRef cgImage1 = [NTBitmapUtils createUIImageFromBitmap: tileBitmap1].CGImage;
    CGImageRef cgImage2 = [NTBitmapUtils createUIImageFromBitmap: tileBitmap2].CGImage;
    
    CGSize imageSize = CGSizeMake(CGImageGetWidth(cgImage1), CGImageGetHeight(cgImage1));
    UIGraphicsBeginImageContext(imageSize);
    CGContextRef context = UIGraphicsGetCurrentContext();

    CGContextDrawImage(context, CGRectMake(0, 0, imageSize.width, imageSize.height), cgImage1);
    CGContextDrawImage(context, CGRectMake(0, 0, imageSize.width, imageSize.height), cgImage2);
    
    // Extract image
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
  
    NTBitmap* tileBitmap = [NTBitmapUtils createBitmapFromUIImage:image];

    return [[NTTileData alloc] initWithData: tileBitmap.compressToInternal];
}

@end
