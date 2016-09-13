/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_POPUPDRAWDATA_H_
#define _NUTI_POPUPDRAWDATA_H_

#include "renderers/drawdatas/BillboardDrawData.h"

namespace Nuti {
    class Options;
    class Popup;
    class PopupStyle;
    class ViewState;
    
    class PopupDrawData: public BillboardDrawData {
    public:
        PopupDrawData(Popup& popup, const PopupStyle& style, const Projection& projection, const Options& options, const ViewState& viewState);
        virtual ~PopupDrawData();
    };
    
}

#endif
