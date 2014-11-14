#ifndef CAMERAPANEVENT_H_
#define CAMERAPANEVENT_H_

#include "CameraEvent.h"
#include "core/MapPos.h"
#include "core/MapVec.h"

namespace Nuti {

class CameraPanEvent: public CameraEvent {
public:
	CameraPanEvent();
	virtual ~CameraPanEvent();

	const MapPos& getPos() const;
	void setPos(const MapPos& pos);

	const MapVec& getPosDelta() const;
	void setPosDelta(const MapVec& posDelta);

	bool isUseDelta() const;

	void calculate(Options& options, ViewState& viewState);

private:
	MapPos _pos;

	MapVec _posDelta;

	bool _useDelta;
};

}

#endif
