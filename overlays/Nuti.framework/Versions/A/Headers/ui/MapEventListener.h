#ifndef MAPEVENTLISTENER_H_
#define MAPEVENTLISTENER_H_

#include "core/MapPos.h"

#include <vector>

namespace Nuti {

namespace ClickType {
    /** 
     * Possible click types.
     */
	enum ClickType {
        /**
         * A click caused by pressing down and then releasing the screen.
         */
        CLICK_TYPE_SINGLE,
        /**
         * A click caused by pressing down but not releasing the screen.
         */
        CLICK_TYPE_LONG,
        /**
         * A click caused by two fast consecutive taps on the screen.
         */
        CLICK_TYPE_DOUBLE,
        /**
         * A click caused by two simultaneous taps on the screen.
         */
        CLICK_TYPE_DUAL};
}

class MapClickInfo;
class VectorElementsClickInfo;

/**
 * Listener for events like map and vector element clicks etc.
 */
class MapEventListener {
public:
    /**
     * Constructs an abstract MapEventListener object.
     */
	virtual ~MapEventListener() {}

    /**
     * Listener method that gets called when the map is panned, rotated, tilted or zoomed.
     * The thread this method is called from may vary.
     */
	virtual void onMapMoved() = 0;

    /**
     * Listener method that gets called when a click is performed on an empty area of the map.
     * This method will NOT be called from the main thread.
     * @param mapClickInfo A container that provides information about the click.
     */
	virtual void onMapClicked(const MapClickInfo& mapClickInfo) = 0;

    /**
     * Listener method that gets called when a click is performed on a vector element.
     * If there are multiple vector elements that are located at the click position, then the
     * results will be sorted by their distance to the camera. The closest element will be the first one
     * in the list. This method will NOT be called from the main thread.
     * @param vectorElementsClickInfo A container that provides information about the click.
     */
	virtual void onVectorElementClicked(const VectorElementsClickInfo& vectorElementsClickInfo) = 0;

};

}

#endif
