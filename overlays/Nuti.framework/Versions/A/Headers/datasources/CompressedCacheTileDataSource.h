#ifndef COMPRESSEDCACHETILEDATASOURCE_H_
#define COMPRESSEDCACHETILEDATASOURCE_H_

#include "datasources/TileDataSource.h"
#include "utils/LRUCache.h"

namespace Nuti {

/**
 * A tile data source that loads tiles from another tile data source
 * and caches them in memory as compressed images. This cache is not persistent, tiles 
 * will be cleared once the application closes.
 */
class CompressedCacheTileDataSource : public TileDataSource {
public:
    /**
     * Constructs a CompressedCacheTileDataSource object from tile data source.
     * @param datasource The datasource to be cached.
     */
	CompressedCacheTileDataSource(const std::shared_ptr<TileDataSource>& dataSource);
	virtual ~CompressedCacheTileDataSource();

	virtual std::shared_ptr<TileData> loadTile(const MapTile& mapTile);
    
    virtual void notifyTilesChanged(TilesType tilesType, bool removeTiles);
    
    /**
     * Returns the compressed tile cache capacity.
     * @return The compressed tile cache capacity in bytes.
     */
    unsigned int getCapacity() const;
    
    /**
     * Sets the compressed tile cache capacity. Tiles from this cache can't be drawn directly to the screen,
     * they must first be decompressed which may cause a small delay before they can be seen.
     * The default is 5MB.
     * @return The new compressed tile cache capacity in bytes.
     */
	void setCapacity(unsigned int capacity);

protected:
    LRUCache<long long, std::shared_ptr<std::vector<unsigned char> > > _cache;
    
    std::shared_ptr<TileDataSource> _dataSource;
    
    mutable std::mutex _mutex;

};

}

#endif
