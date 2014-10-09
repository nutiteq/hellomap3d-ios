#ifndef RASTERTILEDATASOURCE_H_
#define RASTERTILEDATASOURCE_H_

#include "TileDataSource.h"

#include <memory>

namespace Nuti {

class MapTile;
class RasterTileBitmap;

/**
 * Abstract base class for raster tile data sources.
 */
class RasterTileDataSource: public TileDataSource {
public:
    /**
     * Constructs an abstract RasterTileDataSource object.
     * @param minZoom The minimum zoom level supported by this data source.
     * @param maxZoom The maximum zoom level supported by this data source.
     */
    RasterTileDataSource(int minZoom, int maxZoom) :
        TileDataSource(minZoom, maxZoom) {}

	virtual ~RasterTileDataSource() {}

    /**
     * Loads the specified raster tile.
     * @param tile The tile to load.
     * @return The raster tile bitmap containing the tile image. If the tile is not available, null may be returned.
     */
	virtual std::shared_ptr<RasterTileBitmap> loadTile(const MapTile& tile) = 0;

};
    
}

#endif
