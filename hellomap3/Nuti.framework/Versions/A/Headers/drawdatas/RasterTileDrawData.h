#ifndef RASTERTILEDRAWDATA_H_
#define RASTERTILEDRAWDATA_H_

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
