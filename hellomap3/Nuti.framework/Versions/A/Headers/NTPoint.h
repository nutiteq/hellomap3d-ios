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


#import "NTMapPos.h"
#import "NTPointGeometry.h"
#import "NTPointStyle.h"
#import "NTVectorElement.h"

/**
 * A geometric point that can be displayed on the map.
 */
__attribute__ ((visibility("default"))) @interface NTPoint : NTVectorElement
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**
 * Creates a polymorphic instance of the given native object. This is used internally by the SDK.
 */
+(NTPoint*)swigCreatePolymorphicInstance:(void*)cPtr swigOwnCObject:(BOOL)cMemoryOwn;

/**
 * Constructs a Point object from a geometry object and a style.<br>
 * @param geometry The geometry object that defines the location of this point.<br>
 * @param style The style that defines what this point looks like.
 */
-(id)initWithGeometry: (NTPointGeometry*)geometry style: (NTPointStyle*)style;
/**
 * Constructs a Point object from a map position and a style.<br>
 * @param pos The map position that defines the location of this point.<br>
 * @param style The style that defines what this point looks like.
 */
-(id)initWithPos: (NTMapPos*)pos style: (NTPointStyle*)style;
-(NTPointGeometry*)getGeometry;
/**
 * Sets the location for this point.<br>
 * @param geometry The new geometry object that defines the location of this point.
 */
-(void)setGeometry: (NTPointGeometry*)geometry;
/**
 * Returns the location of this point.<br>
 * @return The map position that defines the location of this point.
 */
-(NTMapPos*)getPos;
/**
 * Sets the location of this point.<br>
 * @param pos The new map position that defines the location of this point.
 */
-(void)setPos: (NTMapPos*)pos;
/**
 * Returns the style of this point.<br>
 * @return The style that defines what this point looks like.
 */
-(NTPointStyle*)getStyle;
/**
 * Sets a style for this point.<br>
 * @param style The new style that defines what this point looks like.
 */
-(void)setStyle: (NTPointStyle*)style;
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

