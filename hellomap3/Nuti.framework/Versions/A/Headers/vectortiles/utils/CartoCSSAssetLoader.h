/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CARTOCSSASSETLOADER_H_
#define _NUTI_CARTOCSSASSETLOADER_H_

#include "utils/FileUtils.h"
#include "utils/URLFileLoader.h"
#include "utils/Log.h"
#include "vectortiles/CartoCSS/CartoCSSMapLoader.h"

namespace Nuti {
    
    class CartoCSSAssetLoader : public CartoCSS::CartoCSSMapLoader::AssetLoader {
    public:
        CartoCSSAssetLoader(const std::string& basePath, const std::shared_ptr<MBVectorTileStyleSet>& styleSet) : _basePath(basePath), _styleSet(styleSet), _urlFileLoader("CartoCSSAssetLoader", true) { }
        
        virtual std::shared_ptr<std::vector<unsigned char> > load(const std::string& url) const {
            std::shared_ptr<std::vector<unsigned char> > data;
            if (!_urlFileLoader.loadFile(url, data)) {
                std::string fileName = FileUtils::NormalizePath(_basePath + url);
                if (_styleSet) {
                    data = _styleSet->getElement(fileName);
                }
                if (!data) {
                    Log::Errorf("CartoCSSAssetLoader: Failed to load asset: %s", fileName.c_str());
                }
            }
            return data;
        }
    
    private:
        std::string _basePath;
        std::shared_ptr<MBVectorTileStyleSet> _styleSet;
        URLFileLoader _urlFileLoader;
    };
    
}

#endif
