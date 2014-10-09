#ifndef MBTILESRASTERTILEDATASOURCE_H_
#define MBTILESRASTERTILEDATASOURCE_H_

#include "datasources/RasterTileDataSource.h"

namespace sqlite3pp {
class database;
}

namespace Nuti {

/**
 * A raster tile data source that loads tiles from a local Sqlite database.
 * The database must contain table "tiles" with the following fields:
 * "zoom_level" (tile zoom level), "tile_column" (tile x coordinate),
 * "tile_row" (tile y coordinate), "tile_data" (compressed tile image).
 */
class MBTilesRasterTileDataSource : public RasterTileDataSource {
public:
    /**
     * Constructs a MBTilesRasterTileDataSource object.
     * @param minZoom The minimum zoom level supported by this data source.
     * @param maxZoom The maximum zoom level supported by this data source.
     * @param path The path to the local Sqlite database file.
     */
	MBTilesRasterTileDataSource(int minZoom, int maxZoom, const std::string& path);
	virtual ~MBTilesRasterTileDataSource();

	virtual std::shared_ptr<RasterTileBitmap> loadTile(const MapTile& mapTile);

private:
	std::unique_ptr<sqlite3pp::database> _db;

};

}

#endif
