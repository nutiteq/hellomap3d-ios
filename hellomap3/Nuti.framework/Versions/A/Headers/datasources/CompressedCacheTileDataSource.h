/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_COMPRESSEDCACHETILEDATASOURCE_H_
#define _NUTI_COMPRESSEDCACHETILEDATASOURCE_H_

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
                
        virtual void clear();

        virtual unsigned int getCapacity() const;
        
        virtual void setCapacity(unsigned int capacity);
    
    protected:
        LRUCache<long long, std::shared_ptr<TileData> > _cache;
        mutable std::recursive_mutex _mutex;
    };
    
}

#endif
