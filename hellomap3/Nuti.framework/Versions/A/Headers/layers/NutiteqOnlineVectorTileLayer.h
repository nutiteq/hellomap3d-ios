/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NUTITEQONLINEVECTORTILELAYER_H_
#define _NUTI_NUTITEQONLINEVECTORTILELAYER_H_

#include "VectorTileLayer.h"

#include <string>

namespace Nuti {
    /**
     * Specialized online vector tile layer that connects to Nutiteq online tile server.
     * This layer is intended as a 'shortcut' to make using Nutiteq online service and
     * vector tiles as simple as possible.
     */
    class NutiteqOnlineVectorTileLayer : public VectorTileLayer {
    public:
        /**
         * Constructs a NutiteqOnlineVectorTileLayer object from a style asset name.
         * Uses "nutiteq.osm" as a source.
         * Style asset must be included in the project, style asset defines visual style of the map.
         * @param styleAssetName The name of the style asset that defines visual style of the map.
         */
        NutiteqOnlineVectorTileLayer(const std::string& styleAssetName);
        /**
         * Constructs a NutiteqOnlineVectorTileLayer object from a source name and style asset name.
         * Style asset must be included in the project, style asset defines visual style of the map.
         * @param source The tile source name. Main and default source is currently "nutiteq.osm".
         * @param styleAssetName The name of the style asset that defines visual style of the map.
         */
        NutiteqOnlineVectorTileLayer(const std::string& source, const std::string& styleAssetName);
        virtual ~NutiteqOnlineVectorTileLayer();
        
    private:
        static std::shared_ptr<TileDataSource> CreateDataSource(const std::string& source);
        static std::shared_ptr<VectorTileDecoder> CreateTileDecoder(const std::string& syleAssetName);
        
        static const std::string DEFAULT_SOURCE;
    };
    
}

#endif
