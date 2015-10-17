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


#import "NTGeometry.h"
#import "NTMultiGeometry.h"
#import "NTPointGeometry.h"
#import "NTPointGeometryVector.h"

/**
 * A multipoint container.
 */
__attribute__ ((visibility("default"))) @interface NTMultiPointGeometry : NTMultiGeometry
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**
 * Creates a polymorphic instance of the given native object. This is used internally by the SDK.
 */
+(NTMultiPointGeometry*)swigCreatePolymorphicInstance:(void*)cPtr swigOwnCObject:(BOOL)cMemoryOwn;

/**
 * Constructs a MultiPointGeometry from the vector of points.
 */
-(id)initWithGeometries: (NTPointGeometryVector*)geometries;
/**
 * Returns the point geometry at the specified index. Index must be between 0 and getGeometryCount (exclusive)<br>
 * @return The point geometry at specified index.
 */
-(NTPointGeometry*)getGeometry: (int)index;
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

