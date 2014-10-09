#ifndef MBVECTORTILEDECODER_H_
#define MBVECTORTILEDECODER_H_

#include "VectorTileDecoder.h"
#include "MBVectorTileStyleSet.h"

#include <memory>
#include <mutex>

#include <cglib/mat.h>

namespace Nuti {

namespace Mapnik { class Map; }
namespace MapnikVT { class TileSymbolizerContext; }

/**
 * Decoder for vector tiles in MapBox format.
 */
class MBVectorTileDecoder : public VectorTileDecoder {
public:
	/**
	 * Constructs decoder for MapBox vector tiles based on given style set.
	 * @param styleSet Style set for the tiles.
	 */
	MBVectorTileDecoder(const std::shared_ptr<MBVectorTileStyleSet>& styleSet);
	virtual ~MBVectorTileDecoder();

	/**
	 * Updates relative scale of geometry elements (lines). Default is 1.0f.
	 * Warning: changing this value may corrupt map appearance.
	 * @param scale New relative scale (1.0f is the default).
	 */
	void setGeometryScale(float scale);

	/**
	 * Updates the relative scale of billboard and text elements. Default is 1.0f.
	 * Warning: changing this value may corrupt map appearance.
	 * @param scale New relative scale (1.0f is the default).
	 */
	void setBillboardScale(float scale);

	virtual Color getBackgroundColor() const;

	virtual std::shared_ptr<VT::BitmapPattern> getBackgroundPattern() const;
    
	virtual int getMinZoom() const;
    
	virtual int getMaxZoom() const;

	virtual std::shared_ptr<VT::Tile> decodeTile(const VT::TileId& tile, const VT::TileId& targetTile, const std::shared_ptr<VectorTileData>& data) const;

protected:
	static cglib::mat3x3<float> calculateTileTransform(const Nuti::VT::TileId& tileId, const Nuti::VT::TileId& targetTileId);
    
	std::shared_ptr<MBVectorTileStyleSet> _styleSet;
	std::shared_ptr<Mapnik::Map> _map;
	std::shared_ptr<VT::BitmapPattern> _backgroundPattern;
	std::shared_ptr<MapnikVT::TileSymbolizerContext> _symbolizerContext;

	mutable std::mutex _mutex;
};
    
}

#endif
