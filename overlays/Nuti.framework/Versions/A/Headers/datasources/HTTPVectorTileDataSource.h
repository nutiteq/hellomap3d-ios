#ifndef HTTPVECTORTILEDATASOURCE_H_
#define HTTPVECTORTILEDATASOURCE_H_

#include "VectorTileDataSource.h"

#include <string>

namespace Nuti {

/**
 * A vector tile data source that loads tiles using a HTTP connection.
 * The requests are generated using a template scheme, where tags in the baseURL string are replaced with actual values.
 * The following tags are supported: zoom, x, y, xflipped, yflipped, quadkey.
 *
 * For example, if baseURL = "http://tile.openstreetmap.org/{zoom}/{x}/{y}.png" and the requested tile has zoom = 2,
 * x = 1 and y = 3, then the tile will be loaded from the following URL: "http://tile.openstreetmap.org/2/1/3.png".
 */
class HTTPVectorTileDataSource : public VectorTileDataSource {
public:
    /**
     * Constructs a HTTPVectorTileDataSource object.
     * @param minZoom The minimum zoom level supported by this data source.
     * @param maxZoom The maximum zoom level supported by this data source.
     * @param baseURL The base URL containing tags (for example, "http://tile.openstreetmap.org/{zoom}/{x}/{y}.png").
     */
	HTTPVectorTileDataSource(int minZoom, int maxZoom, const std::string& baseURL);
	virtual ~HTTPVectorTileDataSource();

	virtual std::shared_ptr<VectorTileData> loadTile(const MapTile& mapTile);

protected:
	virtual std::string buildTileUrl(const MapTile& tile);

	std::string _baseUrl;

};

}

#endif
