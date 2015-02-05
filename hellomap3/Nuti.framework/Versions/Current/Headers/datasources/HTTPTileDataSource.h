/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_HTTPTILEDATASOURCE_H_
#define _NUTI_HTTPTILEDATASOURCE_H_

#include "TileDataSource.h"

#include <string>
#include <map>
#include <mutex>

namespace Nuti {

    /**
     * A tile data source that loads tiles using a HTTP connection.
     * The requests are generated using a template scheme, where tags in the baseURL string are replaced with actual values.
     * The following tags are supported: zoom, x, y, xflipped, yflipped, quadkey.
     *
     * For example, if baseURL = "http://tile.openstreetmap.org/{zoom}/{x}/{y}.png" and the requested tile has zoom = 2,
     * x = 1 and y = 3, then the tile will be loaded from the following URL: "http://tile.openstreetmap.org/2/1/3.png".
     */
    class HTTPTileDataSource : public TileDataSource {
    public:
        /**
         * Constructs a HTTPTileDataSource object.
         * @param minZoom The minimum zoom level supported by this data source.
         * @param maxZoom The maximum zoom level supported by this data source.
         * @param baseURL The base URL containing tags (for example, "http://tile.openstreetmap.org/{zoom}/{x}/{y}.png").
         */
        HTTPTileDataSource(int minZoom, int maxZoom, const std::string& baseURL);
        virtual ~HTTPTileDataSource();
		
		/**
		 * Returns the current set of HTTP headers used. Initially this set is empty and can be changed with setHTTPHeaders.
		 * @returns The current set of custom HTTP headers.
		 */
		const std::map<std::string, std::string>& getHTTPHeaders() const;
		
		/**
		 * Sets HTTP headers for all requests.
		 * @param headers A map of HTTP headers that will be used in subsequent requests.
		 */
		void setHTTPHeaders(const std::map<std::string, std::string>& headers);
    
        virtual std::shared_ptr<TileData> loadTile(const MapTile& mapTile);
    
    protected:
        virtual std::string buildTileUrl(const MapTile& tile);
    
        std::string _baseUrl;
		std::map<std::string, std::string> _headers;
		mutable std::mutex _mutex;
    };
    
}

#endif
