#ifndef REDRAWREQUESTLISTENER_H_
#define REDRAWREQUESTLISTENER_H_

namespace Nuti {

class RedrawRequestListener {
public:
	virtual ~RedrawRequestListener() {}

	virtual void onRedrawRequested() const = 0;

};

}

#endif
