#ifndef NMLMODELLODTREESQLITEDATASOURCE_H_
#define NMLMODELLODTREESQLITEDATASOURCE_H_

#include "NMLModelLODTreeDataSource.h"

namespace sqlite3pp {
	class database;
}

namespace Nuti {

/**
 * A sqlite database based data source for NML model LOD trees. The database must be created using
 * custom toolkit from Nutiteq that supports several input formats like KMZ or GeoJSON.
 */
class NMLModelLODTreeSqliteDataSource : public NMLModelLODTreeDataSource {
public:
    /**
     * Constructs a NMLModelLODTreeSqliteDataSource object.
	 * @param proj The projection for the database. Currently only EPSG3857 is supported.
	 * @param fileName The file name of the sqlite database file.
	 */
	NMLModelLODTreeSqliteDataSource(std::shared_ptr<Projection> projection, const std::string& fileName);
	virtual ~NMLModelLODTreeSqliteDataSource();

	virtual MapTileList loadMapTiles(const ViewState& viewState);
	virtual std::shared_ptr<NMLModelLODTree> loadModelLODTree(const MapTile& mapTile);
	virtual std::shared_ptr<NMLPackage::Mesh> loadMesh(long long meshId);
	virtual std::shared_ptr<NMLPackage::Texture> loadTexture(long long textureId, int level);

private:
	std::unique_ptr<sqlite3pp::database> _db;
};

}

#endif
