#ifndef _NUTI_COMBINEDTILEDATASOURCE_H_
#define _NUTI_COMBINEDTILEDATASOURCE_H_

#include "datasources/TileDataSource.h"

namespace Nuti {
	
	/**
	 * A tile data source that combines two data sources (usually offline and online) and selects tiles
	 * based on zoom level. All requests below specified zoom level are directed to the first data source
	 * and all requests at or above specified zoom level are directed to the second data source.
	 */
	class CombinedTileDataSource : public TileDataSource {
	public:
		/**
		 * Constructs a combined tile data source object.
		 * @param dataSource1 First data source that is used if requested tile is below given zoomLevel.
		 * @param dataSource2 Second data source that is used if requested tile is at or above given zoomLevel.
		 * @param zoomLevel Threshold zoom level value.
		 */
		CombinedTileDataSource(const std::shared_ptr<TileDataSource>& dataSource1, const std::shared_ptr<TileDataSource>& dataSource2, int zoomLevel);
		virtual ~CombinedTileDataSource();
		
		virtual std::shared_ptr<TileData> loadTile(const MapTile& tile);
		
	protected:
		class DataSourceListener : public TileDataSource::OnChangeListener {
		public:
			DataSourceListener(CombinedTileDataSource& combinedDataSource);
			
			virtual void onTilesChanged(bool removeTiles);
			
		private:
			CombinedTileDataSource& _combinedDataSource;
		};
		
		std::shared_ptr<TileDataSource> _dataSource1;
		std::shared_ptr<TileDataSource> _dataSource2;
		int _zoomLevel;
		
	private:
		std::shared_ptr<DataSourceListener> _dataSourceListener;
	};
	
}

#endif
