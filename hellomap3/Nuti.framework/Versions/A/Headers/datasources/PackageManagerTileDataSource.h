/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */


#ifndef _NUTI_PACKAGEMANAGERTILEDATASOURCE_H_
#define _NUTI_PACKAGEMANAGERTILEDATASOURCE_H_

#ifdef _NUTI_PACKAGEMANAGER_SUPPORT

#include "datasources/TileDataSource.h"
#include "packagemanager/PackageManager.h"

namespace Nuti {

class PackageManager;

    /**
     * A tile data source that loads tiles from package manager.
     */
    class PackageManagerTileDataSource : public TileDataSource {
    public:
        /**
         * Constructs a PackageManagerTileDataSource object.
         * @param packageManager The package manager that is used to retrieve requested tiles.
         */
        PackageManagerTileDataSource(const std::shared_ptr<PackageManager>& packageManager);
        virtual ~PackageManagerTileDataSource();

        virtual std::shared_ptr<TileData> loadTile(const MapTile& mapTile);

    protected:
        class PackageManagerListener : public PackageManager::OnChangeListener {
        public:
            PackageManagerListener(PackageManagerTileDataSource& dataSource);
        		
            virtual void onTilesChanged();
        		
        private:
            PackageManagerTileDataSource& _dataSource;
        };

        std::shared_ptr<PackageManager> _packageManager;

    private:
        std::shared_ptr<PackageManagerListener> _packageManagerListener;
    };

}

#endif

#endif
