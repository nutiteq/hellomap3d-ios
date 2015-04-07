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


#import "Geometry_proxy.h"
#import "GeometrySimplifier_proxy.h"

/**
 * An implementation of Ramer-Douglas-Peucker algorithm for geometry simplification.<br>
 * Simplifier works on lines and polygons.<br>
 * Simplification is done in two passes - first pass uses fast Radial Distance vertex rejection,<br>
 * second pass uses Ramer-Douglas-Peuckerworst algorithm (with worst case quadratic complexity).
 */
__attribute__ ((visibility("default"))) @interface NTDouglasPeuckerGeometrySimplifier : NTGeometrySimplifier
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;
/**
 * Constructs a new simplifier, given tolerance.<br>
 * @param tolerance The maximum error for simplification. The tolerance value multiplied by view size (either height or width) gives maximum error in pixels.
 */
-(id)initWithTolerance: (float)tolerance;
-(NTGeometry*)simplify: (NTGeometry*)geometry scale: (float)scale;

-(void)dealloc;

@end


#ifdef __cplusplus
}
#endif
