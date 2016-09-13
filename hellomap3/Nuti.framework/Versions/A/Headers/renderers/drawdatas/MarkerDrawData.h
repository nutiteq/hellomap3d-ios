/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MARKERDRAWDATA_H_
#define _NUTI_MARKERDRAWDATA_H_

#include "renderers/drawdatas/BillboardDrawData.h"

namespace Nuti {
    class Marker;
    class MarkerStyle;
    
    class MarkerDrawData: public BillboardDrawData {
    public:
        MarkerDrawData(const Marker& marker, const MarkerStyle& style, const Projection& projection);
        virtual ~MarkerDrawData();
    };
    
}

#endif
