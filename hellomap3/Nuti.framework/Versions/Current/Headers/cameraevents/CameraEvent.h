/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CAMERAEVENT_H_
#define _NUTI_CAMERAEVENT_H_

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
