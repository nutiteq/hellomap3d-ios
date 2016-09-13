/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_REDRAWREQUESTLISTENER_H_
#define _NUTI_REDRAWREQUESTLISTENER_H_

namespace Nuti {

    /**
     * An internal listener class for notifying about screen redraw requests.
     */
    class RedrawRequestListener {
    public:
        virtual ~RedrawRequestListener() { }
    
        /**
         * Called when the screen needs to be redrawn.
         */
        virtual void onRedrawRequested() const { }
    };
    
}

#endif
