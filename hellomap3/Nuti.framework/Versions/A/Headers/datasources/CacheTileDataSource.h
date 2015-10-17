/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CACHETILEDATASOURCE_H_
#define _NUTI_CACHETILEDATASOURCE_H_

#include "datasources/TileDataSource.h"
#include "components/DirectorPtr.h"
#include "utils/LRUCache.h"

namespace Nuti {
    
    /**
     * A tile data source that loads tiles from another tile data source and caches them.
     */
    class CacheTileDataSource : public TileDataSource {
    public:
        virtual ~CacheTileDataSource();
        
        virtual void notifyTilesChanged(bool removeTiles);
        
        /**
         * Clear the cache.
         */
        virtual void clear() = 0;
        
        /**
         * Returns the compressed tile cache capacity.
         * @return The compressed tile cache capacity in bytes.
         */
        virtual unsigned int getCapacity() const = 0;
        
        /**
         * Sets the cache capacity.
         * @return The new tile cache capacity in bytes.
         */
        virtual void setCapacity(unsigned int capacity) = 0;

    protected:
        class DataSourceListener : public TileDataSource::OnChangeListener {
        public:
            DataSourceListener(CacheTileDataSource& cacheDataSource);
            
            virtual void onTilesChanged(bool removeTiles);
            
        private:
            CacheTileDataSource& _cacheDataSource;
        };
        
        CacheTileDataSource(const std::shared_ptr<TileDataSource>& dataSource);

        const DirectorPtr<TileDataSource> _dataSource;
        
    private:
        std::shared_ptr<DataSourceListener> _dataSourceListener;
    };
    
}

#endif
