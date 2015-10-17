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

/**
 * Possible orientation modes for billboards.
 */
typedef NS_ENUM(NSInteger, NTBillboardOrientation) {
/**
 * Billboard always faces the camera plane, regardless of rotation.
 */
  NT_BILLBOARD_ORIENTATION_FACE_CAMERA,
/**
 * Billboard lies parallel to the ground and rotates around it's<br>
 * anchor point to face the camera. SetRotation can be used to offset the<br>
 * final angle of the billboard.
 */
  NT_BILLBOARD_ORIENTATION_FACE_CAMERA_GROUND,
/**
 * Billboard lies on the ground, orientation does not depend on the <br>
 * camera position.
 */
  NT_BILLBOARD_ORIENTATION_GROUND
};

/**
 * Possible scaling modes for billboards.
 */
typedef NS_ENUM(NSInteger, NTBillboardScaling) {
/**
 * Billboard has a constant world space size. Zooming causes the billboard<br>
 * to get smaller or bigger on the screen.
 */
  NT_BILLBOARD_SCALING_WORLD_SIZE,
/**
 * Billboard's size on screen is unaffected by zooming, but billboards<br>
 * that are further away from the camera get smaller when the tilt angle is &lt; 90.
 */
  NT_BILLBOARD_SCALING_SCREEN_SIZE,
/**
 * Billboard's screen size is always the same, regardless of the zoom level, tilt angle or<br>
 * billboard's position.
 */
  NT_BILLBOARD_SCALING_CONST_SCREEN_SIZE
};


#import "NTColor.h"
#import "NTStyle.h"

/**
 * A base class for BillboardStyle subclasses.
 */
__attribute__ ((visibility("default"))) @interface NTBillboardStyle : NTStyle
-(void*)getCptr;
-(id)initWithCptr: (void*)cptr swigOwnCObject: (BOOL)ownCObject;

/**
 * Creates a polymorphic instance of the given native object. This is used internally by the SDK.
 */
+(NTBillboardStyle*)swigCreatePolymorphicInstance:(void*)cPtr swigOwnCObject:(BOOL)cMemoryOwn;

/**
 * Returns the horizontal attaching anchor point of the billoard.<br>
 * @return The horizontal attaching anchor point of the billoard.
 */
-(float)getAttachAnchorPointX;
/**
 * Returns the vertical attaching anchor point of the billoard.<br>
 * @return The vertical attaching anchor point of the billoard.
 */
-(float)getAttachAnchorPointY;
/**
 * Returns the state of the causes overlap flag.<br>
 * @return True if this billboard causes overlapping with other billboards behind it.
 */
-(BOOL)isCausesOverlap;
/**
 * Returns the state of the allow overlap flag.<br>
 * @return True if this billboard can be hidden by overlapping billboards in front of it.
 */
-(BOOL)isHideIfOverlapped;
/**
 * Returns the horizontal offset of the billboard.<br>
 * @return The horizontal offset of the billboard, units depend on the scaling mode.
 */
-(float)getHorizontalOffset;
/**
 * Returns the vertical offset of the billboard.<br>
 * @return The vertical offset of the billboard, units depend on the scaling mode.
 */
-(float)getVerticalOffset;
/**
 * Returns the placement priority of the billboard.<br>
 * @return The placement priority of the billboard.
 */
-(int)getPlacementPriority;
/**
 * Returns the state of the scale with DPI flag.<br>
 * @return True if this billboard's size will be scaled using the screen dot's per inch parameter.
 */
-(BOOL)isScaleWithDPI;
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

