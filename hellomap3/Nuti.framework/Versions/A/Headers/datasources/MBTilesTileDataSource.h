/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MBTILESTILEDATASOURCE_H_
#define _NUTI_MBTILESTILEDATASOURCE_H_

#include "datasources/TileDataSource.h"

#include <map>

namespace sqlite3pp {
    class database;
}
    
namespace Nuti {
    
    namespace MBTilesScheme {
        /**
         * MBTiles tile schemes.
         */
        enum MBTilesScheme {
            /**
             * The default scheme. Vertical coordinate is not flipped.
             */
            MBTILES_SCHEME_TMS,
        
            /**
             * Alternative to TMS scheme. Vertical coordinate is flipped.
             */
            MBTILES_SCHEME_XYZ
        };
    }
    
    /**
     * A tile data source that loads tiles from a local Sqlite database.
     * The database must contain table "tiles" with the following fields:
     * "zoom_level" (tile zoom level), "tile_column" (tile x coordinate),
     * "tile_row" (tile y coordinate), "tile_data" (compressed tile image).
     */
    class MBTilesTileDataSource : public TileDataSource {
    public:
		/**
		 * Constructs a MBTilesTileDataSource object. TMS tile scheme is used,
		 * min and max zoom levels are automatically detected.
		 * @param path The path to the local Sqlite database file.
		 */
		MBTilesTileDataSource(const std::string& path);
		
        /**
         * Constructs a MBTilesTileDataSource object. TMS tile scheme is used.
         * @param minZoom The minimum zoom level supported by this data source.
         * @param maxZoom The maximum zoom level supported by this data source.
         * @param path The path to the local Sqlite database file.
         */
        MBTilesTileDataSource(int minZoom, int maxZoom, const std::string& path);
    
        /**
         * Constructs a MBTilesTileDataSource object with specified tile scheme.
         * @param minZoom The minimum zoom level supported by this data source.
         * @param maxZoom The maximum zoom level supported by this data source.
         * @param path The path to the local Sqlite database file.
         * @param scheme Tile scheme to use.
         */
        MBTilesTileDataSource(int minZoom, int maxZoom, const std::string& path, MBTilesScheme::MBTilesScheme scheme);
    
        virtual ~MBTilesTileDataSource();
		
		/**
		 * Get data source metadata information.
		 * Possible parameters can be found in MBTiles specification.
		 * @return Map containing meta data information (parameter names mapped to parameter values).
		 */
		std::map<std::string, std::string> getMetaData() const;
		
        virtual std::shared_ptr<TileData> loadTile(const MapTile& mapTile);
    
    private:
		static int GetMinZoom(const std::string& path);
		static int GetMaxZoom(const std::string& path);
		
        MBTilesScheme::MBTilesScheme _scheme;
        std::unique_ptr<sqlite3pp::database> _db;
        mutable std::mutex _mutex;
    };
    
}

#endif
