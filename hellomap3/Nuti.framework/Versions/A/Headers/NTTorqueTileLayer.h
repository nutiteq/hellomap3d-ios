/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.11
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


#import "NTVectorTileLayer.h"
#import "NTTileDataSource.h"
#import "NTTorqueTileDecoder.h"

/**
 * A vector tile layer for rendering time-based animated point clouds.
 */
__attribute__ ((visibility("default"))) @interface NTTorqueTileLayer : NTVectorTileLayer
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**
 * Creates a polymorphic instance of the given native object. This is used internally by the SDK.
 */
+(NTTorqueTileLayer*)swigCreatePolymorphicInstance:(void*)cPtr swigOwnCObject:(BOOL)cMemoryOwn;

-(id)initWithDataSource: (NTTileDataSource*)dataSource decoder: (NTTorqueTileDecoder*)decoder;
/**
 * Returns the frame count.<br>
 * @return Frame count in the layer.
 */
-(int)getFrameCount;
/**
 * Returns the current frame number.<br>
 * @return The current frame number.
 */
-(int)getFrameNr;
/**
 * Sets the frame number.<br>
 * @param frameNr The frame number to display.
 */
-(void)setFrameNr: (int)frameNr;
/**
 * Returns the actual class name of this object. This is used internally by the SDK.<br>
 * @return The class name of this object.
 */
-(NSString*)swigGetClassName;
/**
 * Returns the pointer to the connected director object. This is used internally by the SDK.<br>
 * @return The pointer to the connected director object or null if director is not connected.
 */
-(void *)swigGetDirectorObject;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif

