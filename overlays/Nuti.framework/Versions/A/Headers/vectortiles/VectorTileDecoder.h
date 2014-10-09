#ifndef VECTORTILEDECODER_H_
#define VECTORTILEDECODER_H_

#include "VectorTileData.h"
#include "graphics/Color.h"

#include <memory>

namespace Nuti {
    
namespace VT { struct TileId; class Tile; struct BitmapPattern; }

/**
 * Abstract base class for vector tile decoders.
 */
class VectorTileDecoder {
public:
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
     * @param tile The tile to load.
     * @return The vector tile data. If the tile is not available, null may be returned.
     */
	virtual std::shared_ptr<VT::Tile> decodeTile(const VT::TileId& tile, const VT::TileId& targetTile, const std::shared_ptr<VectorTileData>& data) const = 0;
};
    
}

#endif
