#ifndef ASSETRASTERTILEDATASOURCE_H_
#define ASSETRASTERTILEDATASOURCE_H_

#include "RasterTileDataSource.h"

#include <string>

namespace Nuti {
    
/**
 * A raster tile data source where each map tile is a seperate image file bundled with the application.
 * The requests are generated using a template scheme, where tags in the basePath string are replaced with actual values.
 * The following tags are supported: zoom, x, y, xflipped, yflipped, quadkey.
 *
 * For example, if basePath = "t{zoom}_{x}_{y}.png" and the requested tile has zoom == 2,
 * x == 1 and y == 3, then the tile will be loaded from the following path: "t2_1_2.png".
 */
class AssetRasterTileDataSource : public RasterTileDataSource {
public:
    /**
     * Constructs an AssetRasterTileDataSource object.
     * @param minZoom The minimum zoom level supported by this data source.
     * @param maxZoom The maximum zoom level supported by this data source.
     * @param basePath The base path containing tags (for example, "t{zoom}_{x}_{y}.png").
     */
	AssetRasterTileDataSource(int minZoom, int maxZoom, const std::string& basePath);
	virtual ~AssetRasterTileDataSource();

	virtual std::shared_ptr<RasterTileBitmap> loadTile(const MapTile& tile);

protected:
	virtual std::string buildAssetPath(const MapTile& tile);

	std::string _basePath;

};

}

#endif
