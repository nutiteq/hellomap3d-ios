#ifndef VECTORTILEDATASOURCE_H_
#define VECTORTILEDATASOURCE_H_

#include "TileDataSource.h"
#include "vectortiles/VectorTileData.h"

#include <memory>

namespace Nuti {

class MapTile;
class Projection;
class VectorTileData;

/**
 * Abstract base class for all vector tile data sources.
 */
class VectorTileDataSource: public TileDataSource {
public:
    /**
     * Constructs an abstract VectorTileDataSource object.
     * @param minZoom The minimum zoom level supported by this data source.
     * @param maxZoom The maximum zoom level supported by this data source.
     */
    VectorTileDataSource(int minZoom, int maxZoom) : TileDataSource(minZoom, maxZoom) { }
    
    virtual ~VectorTileDataSource() { }

// TODO: enable this at later stage
//    /**
//     * Returns the projection of this data source.
//     * @return The projection of the data source.
//     */
//    virtual std::shared_ptr<Projection> getProjection() const { return _projection; }

    /**
     * Loads the specified vector tile.
     * @param tile The tile to load.
     * @return The vector tile data. If the tile is not available, null may be returned.
     */
	virtual std::shared_ptr<VectorTileData> loadTile(const MapTile& tile) = 0;

protected:
//    std::shared_ptr<Projection> _projection;
};
    
}

#endif
