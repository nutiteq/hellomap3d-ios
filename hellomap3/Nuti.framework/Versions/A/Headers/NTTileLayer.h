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

/**
 * The policy to use when looking for tiles that are not available.
 */
typedef NS_ENUM(NSInteger, NTTileSubstitutionPolicy) {
/**
 * Consider all cached/loaded tiles.
 */
  NT_TILE_SUBSTITUTION_POLICY_ALL,
/**
 * Consider only tiles that are currently visible.<br>
 * This is recommended for low-latency data sources, like offline sources.
 */
  NT_TILE_SUBSTITUTION_POLICY_VISIBLE,
/**
 * Never substitute tiles.
 */
  NT_TILE_SUBSTITUTION_POLICY_NONE
};


#import "NTMapPos.h"
#import "NTMapTile.h"
#import "NTTileDataSource.h"
#import "NTLayer.h"

/**
 * An abstract base class for all tile layers.
 */
__attribute__ ((visibility("default"))) @interface NTTileLayer : NTLayer
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;
/**
 * Returns the data source assigned to this layer.<br>
 * @return The tile data source assigned to this layer.
 */
-(NTTileDataSource *)getDataSource;
/**
 * Returns the state of the preloading flag of this layer.<br>
 * @return True if preloading is enabled.
 */
-(BOOL)isPreloading;
/**
 * Sets the state of preloading for this layer. Preloading allows the downloading of tiles that are not<br>
 * currently visible on screen, but are adjacent to ones that are. This means that the user can pan the map without<br>
 * immediately noticing any missing tiles.<br>
 * <br>
 * Enabling this option might introduce a small performance hit on slower devices. It should also be noted that this<br>
 * will considerably increase network traffic if used with online maps. The default is false.<br>
 * @param preloading The new preloading state of the layer.
 */
-(void)setPreloading: (BOOL)preloading;
/**
 * Returns the current tile substitution policy.<br>
 * @return The current substitution policy. Default is TILE_SUBSTITUTION_POLICY_ALL.
 */
-(enum NTTileSubstitutionPolicy)getTileSubstitutionPolicy;
/**
 * Sets the current tile substitution policy.<br>
 * @param policy The new substitution policy. Default is TILE_SUBSTITUTION_POLICY_ALL.
 */
-(void)setTileSubstitutionPolicy: (enum NTTileSubstitutionPolicy)policy;
/**
 * Gets the current zoom level bias for this layer.<br>
 * @return The current zoom level bias for this layer.
 */
-(float)getZoomLevelBias;
/**
 * Sets the zoom level bias for this layer. Higher zoom level bias forces SDK to use more detailed tiles for given view compared to lower zoom bias.<br>
 * The default bias is 0.<br>
 * @param bias The new bias value, both positive and negative fractional values are supported.
 */
-(void)setZoomLevelBias: (float)bias;
/**
 * Calculate tile corresponding to given geographical coordinates and zoom level.<br>
 * Note: zoom level bias is NOT applied, only discrete zoom level is used.<br>
 * @param mapPos Coordinates of the point in data source projection coordinate system.<br>
 * @param zoom Zoom level to use for the tile.<br>
 * @return corresponding map tile.
 */
-(NTMapTile*)calculateMapTile: (NTMapPos*)mapPos zoom: (int)zoom;
/**
 * Calculate origin map coordinates of given map tile.<br>
 * @param mapTile The map tile to use.<br>
 * @return corresponding coordinates of the tile origin in data source projection coordinate system.
 */
-(NTMapPos*)calculateMapTileOrigin: (NTMapTile*)mapTile;
/**
 * Clear layer tile caches. This will release memory allocated to tiles.<br>
 * @param all True if all tiles should be released, otherwise only preloading (invisible) tiles are released.
 */
-(void)clearTileCaches: (BOOL)all;
-(BOOL)isUpdateInProgress;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

