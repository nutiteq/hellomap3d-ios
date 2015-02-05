/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_SQLITENMLMODELLODTREEDATASOURCE_H_
#define _NUTI_SQLITENMLMODELLODTREEDATASOURCE_H_

#include "NMLModelLODTreeDataSource.h"

namespace sqlite3pp {
    class database;
}

namespace Nuti {

    /**
     * A sqlite database based data source for NML model LOD trees. The database must be created using
     * custom toolkit from Nutiteq that supports several input formats like KMZ or GeoJSON.
     */
    class SqliteNMLModelLODTreeDataSource : public NMLModelLODTreeDataSource {
    public:
        /**
         * Constructs a SqliteNMLModelLODTreeDataSource object.
         * @param projection The projection for the database. Currently only EPSG3857 is supported.
         * @param fileName The file name of the sqlite database file.
         */
        SqliteNMLModelLODTreeDataSource(const std::shared_ptr<Projection>& projection, const std::string& fileName);
        virtual ~SqliteNMLModelLODTreeDataSource();

        virtual std::vector<MapTile> loadMapTiles(const std::shared_ptr<CullState>& cullState);
        virtual std::shared_ptr<NMLModelLODTree> loadModelLODTree(const MapTile& mapTile);
        virtual std::shared_ptr<nml::Mesh> loadMesh(long long meshId);
        virtual std::shared_ptr<nml::Texture> loadTexture(long long textureId, int level);

    private:
        std::unique_ptr<sqlite3pp::database> _db;
    };

}

#endif
