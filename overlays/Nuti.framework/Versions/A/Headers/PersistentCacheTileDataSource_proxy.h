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
#import "CacheTileDataSource_proxy.h"

/**
 * A tile data source that loads tiles from another tile data source<br>
 * and caches them in an offline sqlite database. Tiles will remain in the database<br>
 * even after the application is closed.<br>
 * The database contains table "persistent_cache" with the following fields:<br>
 * "tileId" (tile id), "compressed" (compressed tile image),<br>
 * "time" (the time the tile was cached in milliseconds from epoch).<br>
 * Default cache capacity is 50MB.
 */
@interface NTPersistentCacheTileDataSource : NTCacheTileDataSource
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;
/**
 * Constructs a PersistentCacheTileDataSource object from tile data source<br>
 * and a sqlite database. The sqlite database must be writable, if it doesn't exist, an empty one<br>
 * will be created instead.<br>
 * <br>
 * @param databasePath The path to the sqlite database, where the tiles will be cached.
 */
-(id)initWithDataSource: (NTTileDataSource*)dataSource databasePath: (NSString*)databasePath;
-(NTTileData*)loadTile: (NTMapTile*)mapTile;
-(void)clear;
-(unsigned int)getCapacity;
-(void)setCapacity: (unsigned int)capacity;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

