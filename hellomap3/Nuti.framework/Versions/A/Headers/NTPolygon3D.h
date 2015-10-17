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


#import "NTPolygonGeometry.h"
#import "NTPolygon3DStyle.h"
#import "NTVectorElement.h"
#import "NTMapPosVector.h"
#import "NTMapPosVectorVector.h"

/**
 * A geometric 3d polygon that can be displayed on the map.<br>
 * 3d polygons can be concave and have multiple overlapping holes.
 */
__attribute__ ((visibility("default"))) @interface NTPolygon3D : NTVectorElement
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**
 * Creates a polymorphic instance of the given native object. This is used internally by the SDK.
 */
+(NTPolygon3D*)swigCreatePolymorphicInstance:(void*)cPtr swigOwnCObject:(BOOL)cMemoryOwn;

/**
 * Constructs a Polygon3D object from a geometry object and a style.<br>
 * @param geometry The geometry object that defines the location and holes of this 3d polygon.<br>
 * @param style The style that defines what this 3d polygon looks like.<br>
 * @param height The height of this 3d polygon in meters.
 */
-(id)initWithGeometry: (NTPolygonGeometry*)geometry style: (NTPolygon3DStyle*)style height: (float)height;
/**
 * Constructs a Polygon3D object from a vector of map positions and a style.<br>
 * @param poses The vector of map positions that defines the location of this 3d polygon.<br>
 * @param style The style that defines what this 3d polygon looks like.<br>
 * @param height The height of this 3d polygon in meters.
 */
-(id)initWithPoses: (NTMapPosVector*)poses style: (NTPolygon3DStyle*)style height: (float)height;
/**
 * Constructs a Polygon3D object from a vector of map positions, a vector of holes and a style.<br>
 * @param poses The vector of map positions that defines the location of this 3d polygon.<br>
 * @param holes The vector of holes that defines the locations of holes of this 3d polygon.<br>
 * @param style The style that defines what this 3d polygon looks like.<br>
 * @param height The height of this 3d polygon in meters.
 */
-(id)initWithPoses: (NTMapPosVector*)poses holes: (NTMapPosVectorVector*)holes style: (NTPolygon3DStyle*)style height: (float)height;
-(NTPolygonGeometry*)getGeometry;
/**
 * Sets the location for this 3d polygon.<br>
 * @param geometry The new geometry object that defines the location and holes of this 3d polygon.
 */
-(void)setGeometry: (NTPolygonGeometry*)geometry;
/**
 * Returns the vertices that define this 3d polygon.<br>
 * @return The new vector of map positions that define this 3d polygon.
 */
-(NTMapPosVector*)getPoses;
/**
 * Sets the vertices that define this 3d polygon.<br>
 * Note: holes are not affected by this call.<br>
 * @param poses The new vector of map positions that define this 3d polygon.
 */
-(void)setPoses: (NTMapPosVector*)poses;
/**
 * Returns the holes of the 3d polygon.<br>
 * @return The list of holes of the 3d polygon.
 */
-(NTMapPosVectorVector*)getHoles;
/**
 * Sets the holes of the 3d polygon.<br>
 * @param holes The list of holes of the 3d polygon.
 */
-(void)setHoles: (NTMapPosVectorVector*)holes;
/**
 * Returns the height of this 3d polygon.<br>
 * @return The height of this 3d polygon in meters.
 */
-(float)getHeight;
/**
 * Sets the height for this 3d polygon.<br>
 * @param height The new height for this 3d polygon in meters.
 */
-(void)setHeight: (float)height;
/**
 * Returns the style of this 3d polygon.<br>
 * @return The style that defines what this 3d polygon looks like.
 */
-(NTPolygon3DStyle*)getStyle;
/**
 * Sets the style for this 3d polygon.<br>
 * @param style The new style that defines what this 3d polygon looks like.
 */
-(void)setStyle: (NTPolygon3DStyle*)style;
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

