#ifndef BILLBOARDDRAWDATA_H_
#define BILLBOARDDRAWDATA_H_

#include "core/MapPos.h"
#include "drawdatas/VectorElementDrawData.h"
#include "styles/BillboardStyle.h"

#include <atomic>
#include <memory>

namespace Nuti {

class Bitmap;
class Billboard;
class BillboardRenderer;
class BillboardStyle;
class Projection;

class BillboardDrawData : public VectorElementDrawData {
public:
	virtual ~BillboardDrawData();

	float getAnchorPointX() const;
	float getAnchorPointY() const;
    
    float getAspect() const;

    float getAttachAnchorPointX() const;
    float getAttachAnchorPointY() const;

	std::shared_ptr<Billboard> getBaseBillboard() const;

	std::shared_ptr<Bitmap> getBitmap() const;

	const MapPos* getCoords() const;

	bool isFlippable() const;

	float getHorizontalOffset() const;
	float getVerticalOffset() const;
    
    bool isGenMipmaps() const;

	BillboardOrientation::BillboardOrientation getOrientationMode() const;

	bool isCausesOverlap() const;
    bool isHideIfOverlapped() const;
    
    // These two methods may be called from multiple threads at the same time
	bool isOverlapping() const;
    void setOverlapping(bool overlapping);

	float getPlacementPriority() const;

	const MapPos& getPos() const;
    // Used for setting label positon, when it's attached to another billboards
    void setPos(const MapPos& pos);

	float getRotation() const;
    
    bool isScaleWithDPI() const;
    
    BillboardScaling::BillboardScaling getScalingMode() const;

	float getSize() const;

	double getCameraPlaneZoomDistance() const;
	void setCameraPlaneZoomDistance(double cameraPlaneDistance);

	double getScreenBottomDistance() const;
	void setScreenBottomDistance(double screenBottomDistance);

	BillboardRenderer* getRenderer() const;
	void setRenderer(BillboardRenderer& renderer);

	void offsetHorizontally(double offset);

protected:
	BillboardDrawData(const Billboard& billboard,
                      const BillboardStyle& style,
                      const Projection& projection,
                      const std::shared_ptr<Bitmap>& bitmap,
                      float anchorPointX,
                      float anchorPointY,
                      bool flippable,
                      BillboardOrientation::BillboardOrientation _orientationMode,
                      BillboardScaling::BillboardScaling _scalingMode,
                      float size);

	float _anchorPointX;
	float _anchorPointY;

    float _aspect;
    
    float _attachAnchorPointX;
    float _attachAnchorPointY;

	std::shared_ptr<Billboard> _baseBillboard;

	std::shared_ptr<Bitmap> _bitmap;

	MapPos _coords[4];

	bool _flippable;

	float _horizontalOffset;
	float _verticalOffset;
    
    bool _genMipmaps;

	BillboardOrientation::BillboardOrientation _orientationMode;

	bool _causesOverlap;
    bool _hideIfOverlapped;
	std::atomic<bool> _overlapping;
    
	int _placementPriority;

	MapPos _pos;

	float _rotation;
    
    bool _scaleWithDPI;
    
    BillboardScaling::BillboardScaling _scalingMode;

	float _size;

	double _cameraPlaneZoomDistance;
	double _screenBottomDistance;

	BillboardRenderer* _renderer;
};

}

#endif
