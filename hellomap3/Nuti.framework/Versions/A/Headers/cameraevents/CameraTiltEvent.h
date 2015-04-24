/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CAMERATILTEVENT_H_
#define _NUTI_CAMERATILTEVENT_H_

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
