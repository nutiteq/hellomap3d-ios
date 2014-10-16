#ifndef CACHETILEDATASOURCE_H_
#define CACHETILEDATASOURCE_H_

#include "datasources/TileDataSource.h"
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

		std::shared_ptr<TileDataSource> _dataSource;
		
	private:
		std::shared_ptr<DataSourceListener> _dataSourceListener;
	};
	
}

#endif
