#ifndef COMPRESSEDCACHETILEDATASOURCE_H_
#define COMPRESSEDCACHETILEDATASOURCE_H_

#include "datasources/CacheTileDataSource.h"
#include "utils/LRUCache.h"

namespace Nuti {

/**
 * A tile data source that loads tiles from another tile data source
 * and caches them in memory as compressed images. This cache is not persistent, tiles 
 * will be cleared once the application closes. Default cache capacity is 6MB.
 */
class CompressedCacheTileDataSource : public CacheTileDataSource {
public:
    /**
     * Constructs a CompressedCacheTileDataSource object from tile data source.
     * @param dataSource The datasource to be cached.
     */
	CompressedCacheTileDataSource(const std::shared_ptr<TileDataSource>& dataSource);
	virtual ~CompressedCacheTileDataSource();

	virtual std::shared_ptr<TileData> loadTile(const MapTile& mapTile);
    
    virtual unsigned int getCapacity() const;
    
	virtual void setCapacity(unsigned int capacity);
	
	virtual void clear();

protected:
    LRUCache<long long, std::shared_ptr<std::vector<unsigned char> > > _cache;
};

}

#endif
