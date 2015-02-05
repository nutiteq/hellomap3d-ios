/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_REDRAWREQUESTLISTENER_H_
#define _NUTI_REDRAWREQUESTLISTENER_H_

namespace Nuti {

    class RedrawRequestListener {
    public:
        virtual ~RedrawRequestListener() {}
    
        virtual void onRedrawRequested() const = 0;
    };
    
}

#endif
