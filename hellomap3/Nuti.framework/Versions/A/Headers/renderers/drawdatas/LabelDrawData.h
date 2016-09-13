/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_LABELDRAWDATA_H_
#define _NUTI_LABELDRAWDATA_H_

#include "renderers/drawdatas/BillboardDrawData.h"

namespace Nuti {
    class Label;
    class LabelStyle;
    class ViewState;
    
    class LabelDrawData: public BillboardDrawData {
    public:
        LabelDrawData(const Label& label, const LabelStyle& style,
                      const Projection& projection, const ViewState& viewState);
        virtual ~LabelDrawData();
    };
    
}

#endif
