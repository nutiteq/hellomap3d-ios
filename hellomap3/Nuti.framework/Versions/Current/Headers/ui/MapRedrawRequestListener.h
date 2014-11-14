#ifndef MAPREDRAWREQUESTLISTENER
#define MAPREDRAWREQUESTLISTENER

#import "ui/RedrawRequestListener.h"

@class NTMapViewController;

namespace Nuti {

class MapRedrawRequestListener : public RedrawRequestListener {
public:
    MapRedrawRequestListener(NTMapViewController* mapViewController);
    virtual ~MapRedrawRequestListener();
    
    virtual void onRedrawRequested() const;
    
private:
    __weak NTMapViewController* _mapViewController;
    
};
    
}

#endif