/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.6
 * 
 * This file is not intended to be easily readable and contains a number of 
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG 
 * interface file instead. 
 * ----------------------------------------------------------------------------- */

#import <Foundation/Foundation.h>


#ifdef __cplusplus
extern "C" {
#endif


#import "MapTile_proxy.h"
#import "TileData_proxy.h"
#import "TileDataSource_proxy.h"

/**
 * A tile data source that loads tiles from another tile data source and caches them.
 */
@interface NTCacheTileDataSource : NTTileDataSource
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;
-(void)notifyTilesChanged: (BOOL)removeTiles;
/**
 * Clear the cache.
 */
-(void)clear;
/**
 * Returns the compressed tile cache capacity.<br>
 * @return The compressed tile cache capacity in bytes.
 */
-(unsigned int)getCapacity;
/**
 * Sets the cache capacity.<br>
 * @return The new tile cache capacity in bytes.
 */
-(void)setCapacity: (unsigned int)capacity;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

