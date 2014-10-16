#ifndef RASTERTILEDATASOURCE_H_
#define RASTERTILEDATASOURCE_H_

#include "TileDataSource.h"

#include <memory>

namespace Nuti {

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
};
    
}

#endif
