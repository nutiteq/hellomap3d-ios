#ifndef CAMERAROTATIONEVENT_H_
#define CAMERAROTATIONEVENT_H_

#include "CameraEvent.h"
#include "core/MapPos.h"

namespace Nuti {

class CameraRotationEvent: public CameraEvent {
public:
	CameraRotationEvent();
	virtual ~CameraRotationEvent();

	float getRotation() const;
	void setRotation(float rotation);

	float getRotationDelta() const;
	void setRotationDelta(float rotationDelta);
	void setRotationDelta(double sin, double cos);
    
    const MapPos& getTargetPos() const;
	void setTargetPos(const MapPos& targetPos);

	bool isUseDelta() const;
	bool isUseTarget() const;

	void calculate(Options& options, ViewState& viewState);
    
private:
	float _rotation;

	double _sin;
	double _cos;

	MapPos _targetPos;

	bool _useDelta;
	bool _useTarget;
};

}

#endif
