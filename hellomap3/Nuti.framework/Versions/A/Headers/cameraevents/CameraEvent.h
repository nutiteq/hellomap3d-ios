#ifndef CAMERAEVENT_H_
#define CAMERAEVENT_H_

namespace Nuti {

class Options;
class ViewState;

class CameraEvent {
public:
	virtual ~CameraEvent() {}

	virtual void calculate(Options& options, ViewState& viewState) = 0;

protected:
	CameraEvent() {}
};

}

#endif
