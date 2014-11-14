#ifndef VECTORTILEDECODER_H_
#define VECTORTILEDECODER_H_

#include "core/TileData.h"
#include "graphics/Color.h"

#include <memory>
#include <mutex>

namespace Nuti {
    
namespace VT { struct TileId; class Tile; struct BitmapPattern; }

/**
 * Abstract base class for vector tile decoders.
 */
class VectorTileDecoder {
public:
	/**
	 * Interface for monitoring decoder parameter change events.
	 */
	struct OnChangeListener {
		virtual ~OnChangeListener() { }

		/**
		 * Listener method that gets called when decoder parameters have changed and need to be updated.
		 */
		virtual void onDecoderChanged() = 0;
	};

	virtual ~VectorTileDecoder() { }

    /**
     * Returns background color for tiles.
     * @return Background color for tiles.
     */
	virtual Color getBackgroundColor() const = 0;

    /**
     * Returns background pattern image for tiles.
     * @return background pattern image for tiles.
     */
	virtual std::shared_ptr<VT::BitmapPattern> getBackgroundPattern() const = 0;
    
    /**
     * Returns minimum zoom level supported for by the decoder (or style).
     * @return Minimum supported zoom level.
     */
    virtual int getMinZoom() const = 0;

    /**
     * Returns maximum zoom level supported for by the decoder (or style).
     * @return Maximum supported zoom level.
     */
    virtual int getMaxZoom() const = 0;
    
    /**
     * Loads the specified vector tile.
     * @param tile The id of the tile to load.
	 * @param targetTile The target tile id that will be created from the data.
	 * @param data The tile data to decode.
     * @return The vector tile data. If the tile is not available, null may be returned.
     */
	virtual std::shared_ptr<VT::Tile> decodeTile(const VT::TileId& tile, const VT::TileId& targetTile, const std::shared_ptr<TileData>& data) const = 0;

	/**
	 * Notifies listeners that the decoder parameters have changed. Action taken depends on the implementation of the
	 * listeners, but generally all cached tiles will be reloaded. 
	 */
	virtual void notifyDecoderChanged();
	
	/**
	 * Registers listener for decoder change events.
	 * @param listener The listener for change events.
	 */
	void registerOnChangeListener(const std::shared_ptr<OnChangeListener>& listener);

	/**
	 * Unregisters listener from decoder change events.
	 * @param listener The previously added listener.
	 */
	void unregisterOnChangeListener(const std::shared_ptr<OnChangeListener>& listener);
	
protected:
	mutable std::mutex _mutex;
	
private:
	std::vector<std::shared_ptr<OnChangeListener> > _onChangeListeners;
};
	
}

#endif
