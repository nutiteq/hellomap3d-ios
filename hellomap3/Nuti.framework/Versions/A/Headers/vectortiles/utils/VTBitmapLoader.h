/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VTBITMAPLOADER_H_
#define _NUTI_VTBITMAPLOADER_H_

#include "graphics/Bitmap.h"
#include "vectortiles/MBVectorTileStyleSet.h"
#include "utils/FileUtils.h"
#include "utils/URLFileLoader.h"
#include "utils/Log.h"
#include "vectortiles/VT/Bitmap.h"
#include "vectortiles/VT/BitmapManager.h"

#include <vector>

namespace Nuti {
    
    class VTBitmapLoader : public VT::BitmapManager::BitmapLoader {
    public:
        VTBitmapLoader(const std::string& basePath, const std::shared_ptr<MBVectorTileStyleSet>& styleSet) :  _basePath(basePath), _styleSet(styleSet), _urlFileLoader("VTBitmapLoader", true) { }
    
        virtual std::shared_ptr<VT::Bitmap> load(const std::string& url) const {
            std::shared_ptr<std::vector<unsigned char> > fileData;
            if (!_urlFileLoader.loadFile(url, fileData)) {
                std::string fileName = FileUtils::NormalizePath(_basePath + url);
                if (_styleSet) {
                    fileData = _styleSet->getElement(fileName);
                }
                if (!fileData) {
                    Log::Errorf("VTBitmapLoader: Failed to load bitmap: %s", fileName.c_str());
                }
            }
            if (!fileData) {
                return std::shared_ptr<VT::Bitmap>();
            }
            
            std::shared_ptr<Bitmap> sourceBitmap = Bitmap::CreateFromCompressed(fileData->data(), fileData->size(), false);
            if (!sourceBitmap) {
                Log::Errorf("VTBitmapLoader: Failed to decode bitmap: %s", url.c_str());
                return std::shared_ptr<VT::Bitmap>();                
            }
            sourceBitmap = sourceBitmap->getRGBABitmap(false);
            std::vector<std::uint32_t> data(sourceBitmap->getWidth() * sourceBitmap->getHeight());
            for (unsigned int y = 0; y < sourceBitmap->getHeight(); y++) {
                int dataOffset = (sourceBitmap->getHeight() - 1 - y) * sourceBitmap->getWidth();
                int bitmapOffset = y * sourceBitmap->getWidth() * sourceBitmap->getBytesPerPixel();
                for (unsigned int x = 0; x < sourceBitmap->getWidth(); x++) {
                    data[dataOffset++] = *reinterpret_cast<const std::uint32_t*>(&sourceBitmap->getPixelData()[bitmapOffset]);
                    bitmapOffset += 4;
                }
            }
            return std::make_shared<VT::Bitmap>(sourceBitmap->getWidth(), sourceBitmap->getHeight(), std::move(data));
        }
    
    private:
        std::string _basePath;
        std::shared_ptr<MBVectorTileStyleSet> _styleSet;
        URLFileLoader _urlFileLoader;
    };
    
}

#endif
