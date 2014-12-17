/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CAMERAZOOMEVENT_H_
#define _NUTI_CAMERAZOOMEVENT_H_

#include "CameraEvent.h"
#include "core/MapPos.h"

namespace Nuti {

    class CameraZoomEvent: public CameraEvent {
    public:
        CameraZoomEvent();
        virtual ~CameraZoomEvent();
    
        float getZoom() const;
        void setZoom(float zoom);
    
        float getZoomDelta() const;
        void setZoomDelta(float zoomDelta);
        void setScale(float scale);
        
        const MapPos& getTargetPos() const;
        void setTargetPos(const MapPos& targetPos);
    
        bool isUseDelta() const;
        bool isUseTarget() const;
    
        void calculate(Options& options, ViewState& viewState);
    private:
        float _zoom;
    
        float _zoomDelta;
    
        MapPos _targetPos;
    
        bool _useDelta;
        bool _useTarget;
    };
    
}

#endif
