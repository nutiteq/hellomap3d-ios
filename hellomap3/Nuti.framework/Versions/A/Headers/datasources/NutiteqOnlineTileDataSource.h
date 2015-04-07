/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NUTITEQONLINETILEDATASOURCE_H_
#define _NUTI_NUTITEQONLINETILEDATASOURCE_H_

#include "TileDataSource.h"
#include "utils/LRUCache.h"

namespace Nuti {
	
	/**
	 * An online tile data source that connects to Nutiteq tile server.
	 * Tile server is currently used to 
	 */
	class NutiteqOnlineTileDataSource : public TileDataSource {
	public:
		/**
		 * Constructs a NutiteqTileDataSource object.
		 * @param source Tile source id. Currently only "nutiteq.mbstreets" is supported.
		 */
		NutiteqOnlineTileDataSource(const std::string& source);
		virtual ~NutiteqOnlineTileDataSource();
		
		virtual std::shared_ptr<TileData> loadTile(const MapTile& mapTile);
		
	protected:
		std::shared_ptr<TileData> loadOnlineTile(const MapTile& mapTile);

		std::string _source;
		LRUCache<long long, std::shared_ptr<TileData> > _cache;
		mutable std::recursive_mutex _mutex;
	};
	
}

#endif
