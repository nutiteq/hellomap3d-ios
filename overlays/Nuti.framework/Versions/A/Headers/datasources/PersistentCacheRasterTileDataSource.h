#ifndef PERSISTENTCACHERASTERTILEDATASOURCE_H_
#define PERSISTENTCACHERASTERTILEDATASOURCE_H_

#include "datasources/RasterTileDataSource.h"

#include <list>
#include <string>
#include <unordered_map>

namespace sqlite3pp {
	class database;
}

namespace Nuti {

/**
 * A raster tile data source that loads tiles from another raster tile data source
 * and caches them in an offline sqlite database. Tiles will remain in the database
 * even after the application is closed.
 * The database contains table "persistent_cache" with the following fields:
 * "tileId" (tile id), "compressed" (compressed tile image),
 * "time" (the time the tile was cached in milliseconds from epoch).
 */
class PersistentCacheRasterTileDataSource : public RasterTileDataSource {
public:
    /**
     * Constructs a PersistentCacheRasterTileDataSource object from raster tile data source
     * and a sqlite database. The sqlite database must be writable, if it doesn't exist, an empty one
     * will be created instead.
     * @param datasource The datasource to be cached.
     * @param databasePath The path to the sqlite database, where the tiles will be cached.
     */
	PersistentCacheRasterTileDataSource(const std::shared_ptr<RasterTileDataSource>& dataSource, const std::string& databasePath);
	virtual ~PersistentCacheRasterTileDataSource();

	virtual std::shared_ptr<RasterTileBitmap> loadTile(const MapTile& mapTile);
    
    virtual void notifyTilesChanged(TilesType tilesType, bool removeTiles);
    
    /**
     * Returns the presistent raster tile cache capacity.
     * @return The persistent raster tile cache capacity in bytes.
     */
    unsigned int getCapacity() const;
    /**
     * Sets the persistent tile cache capacity. Tiles from this cache can't be drawn directly to the screen, 
     * they must first be read from the disk and decompressed which may cause a small delay before they can be seen.
     * The default is 50MB.
     * @return The new persistent raster tile cache capacity in bytes.
     */
	void setCapacity(unsigned int capacity);

protected:
    struct CacheElement {
		CacheElement(long long tileId, unsigned int sizeInBytes);
		long long _tileId;
		unsigned int _sizeInBytes;
	};
    
    typedef std::list<CacheElement> CacheElementList;
	typedef std::unordered_map<long long, CacheElementList::iterator> CacheElementItMap;
    
    void openDatabase(const std::string& databasePath);
    void closeDatabase();
    
    void loadTileSet();
    
    void removeOldestElements();
    
	std::shared_ptr<RasterTileBitmap> get(long long tileId);
    
	void remove(long long tileId);
	void removeAll();
    
    void store(long long tileId, const std::shared_ptr<RasterTileBitmap>& tileBitmap);
    
    std::shared_ptr<RasterTileDataSource> _dataSource;
    
    std::unique_ptr<sqlite3pp::database> _database;
    
    unsigned int _capacityInBytes;
	unsigned int _sizeInBytes;
    
    CacheElementList _lruElements;
	CacheElementItMap _mappedElements;
    
    mutable std::mutex _mutex;

};

}

#endif
