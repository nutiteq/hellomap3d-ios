/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CARTOCSS_TORQUECARTOCSSMAPLOADER_H_
#define _NUTI_CARTOCSS_TORQUECARTOCSSMAPLOADER_H_

#include <string>
#include <vector>
#include <memory>

#include "CartoCSSMapLoader.h"
#include "MapnikVT/TorqueMap.h"
#include "MapnikVT/Logger.h"

namespace Nuti { namespace CartoCSS {
    class TorqueCartoCSSMapLoader : protected CartoCSSMapLoader {
    public:
        explicit TorqueCartoCSSMapLoader(std::shared_ptr<AssetLoader> assetLoader, std::shared_ptr<MapnikVT::Logger> logger) : CartoCSSMapLoader(std::move(assetLoader), std::move(logger)) { }

        std::shared_ptr<MapnikVT::TorqueMap> loadMap(const std::string& cartoCSS) const;

    protected:
        void loadTorqueSettings(const std::map<std::string, Value>& mapProperties, MapnikVT::TorqueMap::TorqueSettings& torqueSettings) const;
    };
} }

#endif
