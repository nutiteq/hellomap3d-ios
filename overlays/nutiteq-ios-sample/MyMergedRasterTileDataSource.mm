#import "MyMergedRasterTileDataSource.h"

@interface  MyMergedRasterTileDataSource() {
}

@property (strong, nonatomic) NTRasterTileDataSource* dataSource1;
@property (strong, nonatomic) NTRasterTileDataSource* dataSource2;

@end;

@implementation MyMergedRasterTileDataSource

-(id)initWithDataSource1: (NTRasterTileDataSource*)dataSource1 dataSource2: (NTRasterTileDataSource*)dataSource2
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

-(NTRasterTileBitmap*)loadTile: (NTMapTile*)tile
{
    NTRasterTileBitmap* tileBitmap1 = [_dataSource1 loadTile:tile];
    NTRasterTileBitmap* tileBitmap2 = [_dataSource2 loadTile:tile];

    if (!tileBitmap1) {
        return tileBitmap2;
    }
    
    if (!tileBitmap2) {
        return tileBitmap1;
    }
    
    // Combine the bitmaps
    CGImageRef cgImage1 = [NTBitmapUtils createUIImageFromBitmap:[tileBitmap1 getBitmap]].CGImage;
    CGImageRef cgImage2 = [NTBitmapUtils createUIImageFromBitmap:[tileBitmap2 getBitmap]].CGImage;
    
    CGSize imageSize = CGSizeMake(CGImageGetWidth(cgImage1), CGImageGetHeight(cgImage1));
    UIGraphicsBeginImageContext(imageSize);
    CGContextRef context = UIGraphicsGetCurrentContext();

    CGContextDrawImage(context, CGRectMake(0, 0, imageSize.width, imageSize.height), cgImage1);
    CGContextDrawImage(context, CGRectMake(0, 0, imageSize.width, imageSize.height), cgImage2);
    
    // Extract image
    UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();

    return [[NTRasterTileBitmap alloc] initWithBitmap:[NTBitmapUtils createBitmapFromUIImage:image]];
}

@end
