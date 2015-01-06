/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_TILELOADLISTENER_H_
#define _NUTI_TILELOADLISTENER_H_

namespace Nuti {

    // TileLoadListener should be nested inside RasterTileLayer but Swig 2 doesn't support nested classes
    /**
     * Interface for monitoring tile loading events.
     */
    class TileLoadListener {
    public:
        virtual ~TileLoadListener() {}
        /**
         * Listener method that gets called when all visible raster tiles have finished loading.
         */
        virtual void onVisibleTilesLoaded() = 0;
    
        /**
         * Listener method that gets called when all preloading raster tiles have finished loading.
         * This method gets called after onVisibleTilesLoaded() and only if preloading is enabled.
         */
        virtual void onPreloadingTilesLoaded() = 0;
    };
        
}

#endif
