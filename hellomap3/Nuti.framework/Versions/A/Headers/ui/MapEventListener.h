/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPEVENTLISTENER_H_
#define _NUTI_MAPEVENTLISTENER_H_

#include "core/MapPos.h"

#include <vector>
#include <memory>

namespace Nuti {
    class MapClickInfo;
    class VectorElementsClickInfo;
    
    /**
     * Listener for events like map and vector element clicks etc.
     */
    class MapEventListener {
    public:
        virtual ~MapEventListener() { }
    
        /**
         * Listener method that gets called at the end of the rendering process when the
         * map view needs no further refreshing.
         * Note that there can still be background processes (tile loading) that may change
         * the map view but these may take long time.
         * This method is called from GL renderer thread, not from main thread.
         */
        virtual void onMapIdle() { }

        /**
         * Listener method that gets called when the map is panned, rotated, tilted or zoomed.
         * The thread this method is called from may vary.
         */
        virtual void onMapMoved() { }
        
        /**
         * Listener method that gets called when map is in 'stable' state - map animations have finished,
         * user has lifted fingers from the screen. This method is similar to onMapIdle, but is called less
         * frequently and takes account touch state.
         * The thread this method is called from may vary.
         */
        virtual void onMapStable() { }
    
        /**
         * Listener method that gets called when a click is performed on an empty area of the map.
         * This method will NOT be called from the main thread.
         * @param mapClickInfo A container that provides information about the click.
         */
        virtual void onMapClicked(const std::shared_ptr<MapClickInfo>& mapClickInfo) { }
    
        /**
         * Listener method that gets called when a click is performed on a vector element.
         * If there are multiple vector elements that are located at the click position, then the
         * results will be sorted by their distance to the camera. The closest element will be the first one
         * in the list. This method will NOT be called from the main thread.
         * @param vectorElementsClickInfo A container that provides information about the click.
         */
        virtual void onVectorElementClicked(const std::shared_ptr<VectorElementsClickInfo>& vectorElementsClickInfo) { }
        
        /**
         * Listener method that gets called at the start of the rendering process.
         * The method can be used to synchronize vector elements with renderer state, for example
         * to force marker to be always at the center of the screen (focus point).
         * This method is called from GL renderer thread, not from main thread.
         */
        virtual void onBeforeDrawFrame() { }
        
        /**
         * Listener method that gets called at the end of the rendering process.
         * This method is called from GL renderer thread, not from main thread.
         */
        virtual void onAfterDrawFrame() { }
    };
    
}

#endif
