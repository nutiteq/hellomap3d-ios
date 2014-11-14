#ifndef BILLBOARDSTYLE_H_
#define BILLBOARDSTYLE_H_

#include "styles/Style.h"

namespace Nuti {

namespace BillboardOrientation {
    /**
     * Possible orientation modes for billboards.
     */
	enum BillboardOrientation {
        /**
         * Billboard always faces the camera plane, regardless of rotation.
         */
        BILLBOARD_ORIENTATION_FACE_CAMERA,
        /**
         * Billboard lies parallel to the ground and rotates around it's
         * anchor point to face the camera. SetRotation can be used to offset the
         * final angle of the billboard.
         */
        BILLBOARD_ORIENTATION_FACE_CAMERA_GROUND,
        /**
         * Billboard lies on the ground, orientation does not depend on the 
         * camera position.
         */
        BILLBOARD_ORIENTATION_GROUND};
};

namespace BillboardScaling {
    /**
     * Possible scaling modes for billboards.
     */
    enum BillboardScaling {
        /**
         * Billboard has a constant world space size. Zooming causes the billboard
         to get smaller or bigger on the screen.
         */
        BILLBOARD_SCALING_WORLD_SIZE,
        /**
         * Billboard's size on screen is unaffected by zooming, but billboards
         * that are further away from the camera get smaller when the tilt angle is < 90.
         */
        BILLBOARD_SCALING_SCREEN_SIZE,
        /**
         * Billboard's screen size is always the same, regardless of the zoom level, tilt angle or
         * billboard's position.
         */
        BILLBOARD_SCALING_CONST_SCREEN_SIZE};
}

class BillboardStyle : public Style {
public:
    /**
     * Constructs a BillboardStyle object from various parameters. Instantiating the object directly is
     * not recommended, BillboardStyleBuilder should be used instead.
     * @param color The color for the billboard.
     * @param attachAnchorPointX The horizontal attaching anchor point for the billboard.
     * @param attachAnchorPointY The vertical attaching anchor point for the billboard.
     * @param causesOverlap The causes overlap flag for the billboard.
     * @param hideIfOverlapped The hide if overlapped flag for the billboard.
     * @param horizontalOffset The horizontal offset for the billboard.
     * @param verticalOffset The vertical offset for the billboard.
     * @param placementPriority The placement priority for the billboard.
     * @param scaleWithDpi The scale with DPI flag for the billboard.
     */
	BillboardStyle(const Color& color,
                   float attachAnchorPointX,
                   float attachAnchorPointY,
                   bool causesOverlap,
                   bool hideIfOverlapped,
                   float horizontalOffset,
                   float verticalOffset,
                   int placementPriority,
                   bool scaleWithDPI);
	virtual ~BillboardStyle();

    /**
     * Returns the horizontal attaching anchor point of the billoard.
     * @return The horizontal attaching anchor point of the billoard.
     */
	float getAttachAnchorPointX() const;
    /**
     * Returns the vertical attaching anchor point of the billoard.
     * @return The vertical attaching anchor point of the billoard.
     */
	float getAttachAnchorPointY() const;
    
    /**
     * Returns the state of the causes overlap flag.
     * @return True if this billboard causes overlapping with other billboards behind it.
     */
    bool isCausesOverlap() const;
    /**
     * Returns the state of the allow overlap flag.
     * @return True if this billboard can be hidden by overlapping billboards in front of it.
     */
    bool isHideIfOverlapped() const;

    /**
     * Returns the horizontal offset of the billboard.
     * @return The horizontal offset of the billboard, units depend on the scaling mode.
     */
	float getHorizontalOffset() const;
    /**
     * Returns the vertical offset of the billboard.
     * @return The vertical offset of the billboard, units depend on the scaling mode.
     */
	float getVerticalOffset() const;

    /**
     * Returns the placement priority of the billboard.
     * @return The placement priority of the billboard.
     */
	int getPlacementPriority() const;
    
    /**
     * Returns the state of the scale with DPI flag.
     * @return True if this billboard's size will be scaled using the screen dot's per inch parameter.
     */
    bool isScaleWithDPI() const;
    
protected:
	float _attachAnchorPointX;
	float _attachAnchorPointY;
    
    bool _causesOverlap;
    bool _hideIfOverlapped;

	float _horizontalOffset;
	float _verticalOffset;

	int _placementPriority;
    
    bool _scaleWithDPI;
    
};

}

#endif
