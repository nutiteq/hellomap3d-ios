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
 * An immutable map tile, used by tile layers for representing small pieces of map at different zoom levels and coordinates.
 */
__attribute__ ((visibility("default"))) @interface NTMapTile : NSObject
{
  void *swigCPtr;
  BOOL swigCMemOwn;
}
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**  
 * Checks if this object is equal to the specified object.
 * @return True when objects are equal, false otherwise.
 */
-(BOOL)isEqual:(id)object;

/**
 * Returns the hash value of this object.
 * @return The hash value of this object.
 */
-(NSUInteger)hash;

-(id)initWithX: (int)x y: (int)y zoom: (int)zoom frameNr: (int)frameNr;
/**
 * Checks for equality between this and another map tile.<br>
 * @param tile The other map tile.<br>
 * @return True if equal.
 */
-(BOOL)isEqualInternal: (NTMapTile*)tile;
/**
 * Returns the x coordinate of this map tile.<br>
 * @return The x coordinate of this map tile.
 */
-(int)getX;
/**
 * Returns the y coordinate of this map tile.<br>
 * @return The y coordinate of this map tile.
 */
-(int)getY;
/**
 * Returns the zoom level of this map tile.<br>
 * @return The zoom level of this map tile.
 */
-(int)getZoom;
/**
 * Returns the time of this map tile.<br>
 * @return The time of this map tile.
 */
-(int)getFrameNr;
/**
 * Returns the internal tile id of this map tile.<br>
 * @return The internal tile id of this map tile.
 */
-(long long)getTileId;
/**
 * Returns the hash value of this object.<br>
 * @return The hash value of this object.
 */
-(int)hashInternal;
/**
 * Creates a string representation of this map tile, useful for logging.<br>
 * @return The string representation of this map tile.
 */
-(NSString*)description;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

