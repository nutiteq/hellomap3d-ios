/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CAMERAPANEVENT_H_
#define _NUTI_CAMERAPANEVENT_H_

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
