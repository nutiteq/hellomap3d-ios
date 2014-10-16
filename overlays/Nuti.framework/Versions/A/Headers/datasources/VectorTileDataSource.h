#ifndef VECTORTILEDATASOURCE_H_
#define VECTORTILEDATASOURCE_H_

#include "TileDataSource.h"

#include <memory>

namespace Nuti {

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
};
    
}

#endif
