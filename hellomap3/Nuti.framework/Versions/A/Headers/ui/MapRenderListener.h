/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPRENDERLISTENER_H_
#define _NUTI_MAPRENDERLISTENER_H_

#include <memory>

namespace Nuti {
    class Bitmap;

    /**
     * Listener for events like map and vector element clicks etc.
     */
    class MapRenderListener {
    public:
        virtual ~MapRenderListener() {}
        
        /**
         * Listener method that is called when the map has been rendered.
         * @param mapBitmap rendered map as bitmap.
         */
        virtual void onMapRendered(const std::shared_ptr<Bitmap>& mapBitmap) { }
    };
    
}

#endif
