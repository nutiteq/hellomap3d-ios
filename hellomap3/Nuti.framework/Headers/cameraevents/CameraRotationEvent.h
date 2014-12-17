/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CAMERAROTATIONEVENT_H_
#define _NUTI_CAMERAROTATIONEVENT_H_

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
