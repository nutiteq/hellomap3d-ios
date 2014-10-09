#ifndef CAMERATILTEVENT_H_
#define CAMERATILTEVENT_H_

#include "CameraEvent.h"

namespace Nuti {

class CameraTiltEvent: public CameraEvent {
public:
	CameraTiltEvent();
	virtual ~CameraTiltEvent();

	float getTilt() const;
	void setTilt(float tilt);

	float getTiltDelta() const;
	void setTiltDelta(float tiltDelta);

	bool isUseDelta() const;

	void calculate(Options& options, ViewState& viewState);
private:
	float _tilt;

	float _tiltDelta;

	float _useDelta;
};

}

#endif
