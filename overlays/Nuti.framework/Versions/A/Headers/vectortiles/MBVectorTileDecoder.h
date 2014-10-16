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
	 * Constructs decoder for MapBox vector tiles based on specified style set.
	 * If the style set contains multiple styles, the first one (based on lexicographical order) from the root folder is chosen.
	 * @param styleSet Style set for the tiles.
	 */
	MBVectorTileDecoder(const std::shared_ptr<MBVectorTileStyleSet>& styleSet);

	/**
	 * Constructs decoder for MapBox vector tiles based on specified style set.
	 * Specified style is selected as the current style.
	 * @param styleSet Style set for the tiles.
	 * @param styleName Style to select.
	 */
	MBVectorTileDecoder(const std::shared_ptr<MBVectorTileStyleSet>& styleSet, const std::string& styleName);

	virtual ~MBVectorTileDecoder();
	
	/**
	 * Returns the current style name.
	 * @return The current style name.
	 */
	const std::string& getCurrentStyleName() const;
	
	/**
	 * Select current style by style name. The style must exist in the style set container specified in the constructor as an xml file.
	 * This call will also reset style-related parameters, like geometry and billboard scales of the decoder.
	 * @param styleName style to use
	 */
	void setCurrentStyle(const std::string& styleName);
	
	/**
	 * Returns the relative scale of geometry elements.
	 * @return The current geometry scale.
	 */
	float getGeometryScale() const;

	/**
	 * Updates relative scale of geometry elements (lines). Default is 1.0f.
	 * @param scale New relative scale (1.0f is the default).
	 */
	void setGeometryScale(float scale);

	/**
	 * Returns the relative scale of billboard elements.
	 * @return The current billboard scale.
	 */
	float getBillboardScale() const;
	
	/**
	 * Updates the relative scale of billboard and text elements. Default is 1.0f.
	 * @param scale New relative scale (1.0f is the default).
	 */
	void setBillboardScale(float scale);

	virtual Color getBackgroundColor() const;

	virtual std::shared_ptr<VT::BitmapPattern> getBackgroundPattern() const;
    
	virtual int getMinZoom() const;
    
	virtual int getMaxZoom() const;

	virtual std::shared_ptr<VT::Tile> decodeTile(const VT::TileId& tile, const VT::TileId& targetTile, const std::shared_ptr<TileData>& data) const;

protected:
	static cglib::mat3x3<float> calculateTileTransform(const Nuti::VT::TileId& tileId, const Nuti::VT::TileId& targetTileId);
	
	std::string _styleName;
	std::shared_ptr<MBVectorTileStyleSet> _styleSet;
	std::shared_ptr<Mapnik::Map> _map;
	std::shared_ptr<VT::BitmapPattern> _backgroundPattern;
	std::shared_ptr<MapnikVT::TileSymbolizerContext> _symbolizerContext;

	mutable std::mutex _mutex;
};
    
}

#endif
