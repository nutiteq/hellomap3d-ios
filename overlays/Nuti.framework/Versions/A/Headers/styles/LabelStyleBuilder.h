#ifndef LABELSTYLEBUILDER_H_
#define LABELSTYLEBUILDER_H_

#include "styles/BillboardStyleBuilder.h"

#include <memory>

namespace Nuti {

class LabelStyle;

/**
 * A builder class for LabelStyle.
 */
class LabelStyleBuilder : public BillboardStyleBuilder {
public:
    /**
     * Constructs a LabelStyleBuilder object with all parameters set to defaults.
     */
	LabelStyleBuilder();
	virtual ~LabelStyleBuilder();
    
    /**
     * Returns the horizontal anchor point of the label.
     * @return The horizontal anchor point of the label.
     */
	float getAnchorPointX() const;
    /**
     * Returns the vertical anchor point of the label.
     * @return The vertical anchor point of the label.
     */
	float getAnchorPointY() const;
    /**
     * Sets the anchor point for the label. Values will be clamped to [-1, 1] range.
     * @param anchorPointX The new horizontal anchor point for the label. -1 means the left side,
     * 0 the center and 1 the right side of the label. The default is 0.
     * @param anchorPointY The vertical anchor point for the label. -1 means the bottom,
     * 0 the center and 1 the top of the label. The default is -1.
     */
	void setAnchorPoint(float anchorPointX, float anchorPointY);
    
    /**
     * Returns the state of the flippable flag.
     * @return True if the label is flippable.
     */
	bool isFlippable() const;
    /**
     * Sets the state of the flippable flag. If set to true and the orientation mode is set to
     * GROUND the label is allowed to flip 180 degrees to try and face the camera better. This is
     * useful for street names and some other texts. The default is true.
     * @param flippable The new state of the flippable flag.
     */
	void setFlippable(bool flippable);
    
    /**
     * Returns the orientation mode of the label.
     * @return The orientation mode of the label.
     */
	BillboardOrientation::BillboardOrientation getOrientationMode() const;
    /**
     * Sets the orientation mode for the label. The default is BillboardOrientation::FACE_CAMERA_BILLBOARD.
     * @return The new orientation mode for the label.
     */
	void setOrientationMode(BillboardOrientation::BillboardOrientation orientationMode);
    
    /**
     * Returns the scaling mode of the label.
     * @return The scaling mode of the label.
     */
    BillboardScaling::BillboardScaling getScalingMode() const;
    /**
     * Sets the scaling mode for the label. The default is BillboardScaling::CONST_SCREEN_SIZE.
     * @return The new scaling mode for the label.
     */
	void setScalingMode(BillboardScaling::BillboardScaling scalingMode);
    
    /**
     * Builds a new instance of the LabelStyle object using previously set parameters.
     * @return A new LabelStyle object.
     */
	std::shared_ptr<LabelStyle> buildStyle();

protected:
    float _anchorPointX;
	float _anchorPointY;
    
    bool _flippable;
    
    BillboardOrientation::BillboardOrientation _orientationMode;
    
    BillboardScaling::BillboardScaling _scalingMode;

};

}

#endif
