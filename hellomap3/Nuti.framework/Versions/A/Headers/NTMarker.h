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
#import "NTBitmap.h"
#import "NTGeometry.h"
#import "NTMarkerStyle.h"
#import "NTBillboard.h"

/**
 * A billboard element with a static bitmap that can be displayed on the map.
 */
__attribute__ ((visibility("default"))) @interface NTMarker : NTBillboard
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**
 * Creates a polymorphic instance of the given native object. This is used internally by the SDK.
 */
+(NTMarker*)swigCreatePolymorphicInstance:(void*)cPtr swigOwnCObject:(BOOL)cMemoryOwn;

/**
 * Constructs a Marker object with the specified style and attaches it to a billboard element.<br>
 * @param baseBillboard The billboard this billboard will be attached to.<br>
 * @param style The style that defines what this marker looks like.
 */
-(id)initWithBaseBillboard: (NTBillboard*)baseBillboard style: (NTMarkerStyle*)style;
/**
 * Constructs a Marker object from a geometry object and a style.<br>
 * @param geometry The geometry object that defines the location of this marker.<br>
 * @param style The style that defines what this marker looks like.
 */
-(id)initWithGeometry: (NTGeometry*)geometry style: (NTMarkerStyle*)style;
/**
 * Constructs a Marker object from a map position and a style.<br>
 * @param pos The map position that defines the location of this marker.<br>
 * @param style The style that defines what this marker looks like.
 */
-(id)initWithPos: (NTMapPos*)pos style: (NTMarkerStyle*)style;
/**
 * Returns the style of this marker.<br>
 * @return The style that defines what this marker looks like.
 */
-(NTMarkerStyle*)getStyle;
/**
 * Sets the style for this marker.<br>
 * @return The new style that defines what this marker looks like.
 */
-(void)setStyle: (NTMarkerStyle*)style;
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

