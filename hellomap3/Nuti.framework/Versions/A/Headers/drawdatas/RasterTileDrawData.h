/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_RASTERTILEDRAWDATA_H_
#define _NUTI_RASTERTILEDRAWDATA_H_

#include "TileDrawData.h"
#include "core/MapBounds.h"

namespace Nuti {
    class MapTileQuadTreeNode;
    
    class RasterTileDrawData : public TileDrawData {
    public:
        RasterTileDrawData(const MapTileQuadTreeNode& requestedTile, const MapTileQuadTreeNode& closestTile, bool preloadingTile);
        virtual ~RasterTileDrawData();
    
        const MapBounds& getCoordBounds() const;
        MapBounds& getCoordBounds();
    
        const MapBounds& getTexCoordBounds() const;
        MapBounds& getTexCoordBounds();
    
        void offsetHorizontally(double offset);
    
    private:
        MapBounds _coordBounds;
        MapBounds _texCoordBounds;
    };
    
}

#endif
