#ifndef TILEDATASOURCE_H_
#define TILEDATASOURCE_H_

#include <mutex>
#include <vector>

namespace Nuti {

/**
 * Possible tiles types.
 */
enum TilesType {
	/**
	 * Tiles that are visible on the screen.
	 */
	TILES_TYPE_VISIBLE,
	/**
	 * Tiles that are not visible on the screen, but are right outside the visible frustum.
	 */
	TILES_TYPE_PRELOADING,
	/**
	 * Both visible and preloading tiles.
	 */
	TILES_TYPE_BOTH
};

/**
 * Abstract base class for tile data sources. It provides default implementation 
 * for listener registration and other common tile data source methods.
 */
class TileDataSource {
public:
    /**
     * Interface for monitoring data source change events.
     */
    struct OnChangeListener {
        /**
         * Listener method that gets called when tiles have changes and need to be updated.
         * If the removeTiles flag is set all caches should be cleared prior to updating.
         * @param tilesType The type of tiles the event affects.
         * @param removeTiles The remove tiles flag.
         */
        virtual void onTilesChanged(TilesType tilesType, bool removeTiles) = 0;
	};
    
	virtual ~TileDataSource();
    
    /**
     * Returns the minimum zoom level supported by this data source.
     * @return The minimum zoom level supported (inclusive).
     */
    int getMinZoom() const;
    /**
     * Returns the maximum zoom level supported by this data source.
     * @return The maximum zoom level supported (exclusive).
     */
    int getMaxZoom() const;
    
    /**
     * Notifies listeners that the tiles have changed. Action taken depends on the implementation of the
     * listeners, but generally all cached tiles will be reloaded. If the removeTiles flag is set all caches will be cleared
     * prior to reloading, if it's not set then the reloaded tiles will replace the old tiles in caches as they finish loading.
     * @param tilesType The type of tiles the event affects.
     * @param removeTiles The remove tiles flag.
     */
    virtual void notifyTilesChanged(TilesType tilesType, bool removeTiles);
    
    /**
     * Registers listener for data source change events.
     * @param listener The listener for change events.
     */
    void registerOnChangeListener(OnChangeListener* listener);
    /**
     * Unregisters listener from data source change events.
     * @param listener The previously added listener.
     */
	void unregisterOnChangeListener(OnChangeListener* listener);

protected:
	TileDataSource(int minZoom, int maxZoom);

	int _minZoom;
	int _maxZoom;

	mutable std::mutex _mutex;
    
private:
	std::vector<OnChangeListener*> _onChangeListeners;
};

}

#endif
