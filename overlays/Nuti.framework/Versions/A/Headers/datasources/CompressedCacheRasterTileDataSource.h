#ifndef COMPRESSEDCACHERASTERTILEDATASOURCE_H_
#define COMPRESSEDCACHERASTERTILEDATASOURCE_H_

#include "datasources/RasterTileDataSource.h"
#include "utils/LRUCache.h"

namespace Nuti {

/**
 * A raster tile data source that loads tiles from another raster tile data source
 * and caches them in memory as compressed images. This cache is not persistent, tiles 
 * will be cleared once the application closes.
 */
class CompressedCacheRasterTileDataSource : public RasterTileDataSource {
public:
    /**
     * Constructs a CompressedCacheRasterTileDataSource object from raster tile data source.
     * @param datasource The datasource to be cached.
     */
	CompressedCacheRasterTileDataSource(const std::shared_ptr<RasterTileDataSource>& dataSource);
	virtual ~CompressedCacheRasterTileDataSource();

	virtual std::shared_ptr<RasterTileBitmap> loadTile(const MapTile& mapTile);
    
    virtual void notifyTilesChanged(TilesType tilesType, bool removeTiles);
    
    /**
     * Returns the compressed raster tile cache capacity.
     * @return The compressed raster tile cache capacity in bytes.
     */
    unsigned int getCapacity() const;
    
    /**
     * Sets the compressed tile cache capacity. Tiles from this cache can't be drawn directly to the screen,
     * they must first be decompressed which may cause a small delay before they can be seen.
     * The default is 5MB.
     * @return The new compressed raster tile cache capacity in bytes.
     */
	void setCapacity(unsigned int capacity);

protected:
    LRUCache<long long, std::shared_ptr<std::vector<unsigned char> > > _cache;
    
    std::shared_ptr<RasterTileDataSource> _dataSource;
    
    mutable std::mutex _mutex;

};

}

#endif
