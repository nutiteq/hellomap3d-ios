/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NUTITEQONLINEVECTORTILELAYER_H_
#define _NUTI_NUTITEQONLINEVECTORTILELAYER_H_

#include "VectorTileLayer.h"

namespace Nuti {
    /**
     * Specialized online vector tile layer that connects to Nutiteq online tile server.
     * This layer is intended as a 'shortcut' to make using Nutiteq online service and vector tiles as simple as possible.
     */
    class NutiteqOnlineVectorTileLayer : public VectorTileLayer {
    public:
        /**
         * Constructs a NutiteqOnlineVectorTileLayer object from a registered API key and a style asset name.
         * Style asset must be included in the project, style asset defines visual style of the map.
         * @param apiKey The registered API key for the app.
         * @param styleAssetName The name of the style asset that defines visual style of the map.
         */
        NutiteqOnlineVectorTileLayer(const std::string& apiKey, const std::string& styleAssetName);
        virtual ~NutiteqOnlineVectorTileLayer();
        
    private:
        static std::shared_ptr<TileDataSource> createDataSource(const std::string& apiKey);
        static std::shared_ptr<VectorTileDecoder> createTileDecoder(const std::string& syleAssetName);
    };
    
}

#endif
