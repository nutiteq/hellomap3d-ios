/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MBVECTORTILEDECODER_H_
#define _NUTI_MBVECTORTILEDECODER_H_

#include "VectorTileDecoder.h"
#include "MBVectorTileStyleSet.h"

#include <memory>
#include <mutex>
#include <map>
#include <string>

#include <cglib/mat.h>

namespace Nuti {
    namespace Mapnik {
        class Map;
        class Value;
    }

    namespace MapnikVT {
        class TileSymbolizerContext;
    }
    
    /**
     * Decoder for vector tiles in MapBox format.
     */
    class MBVectorTileDecoder : public VectorTileDecoder {
    public:
        /**
         * Constructs decoder for MapBox vector tiles based on specified style set.
         * If the style set contains multiple styles, the first one (based on lexicographical order) from the root folder is chosen as the current style.
         * @param styleSet Style set for the tiles.
         */
        MBVectorTileDecoder(const std::shared_ptr<MBVectorTileStyleSet>& styleSet);
    
        /**
         * Constructs decoder for MapBox vector tiles based on specified style set.
         * Specified style is selected as the current style.
         * @param styleSet Style set for the tiles.
         * @param styleName Style to select.
         */
        MBVectorTileDecoder(const std::shared_ptr<MBVectorTileStyleSet>& styleSet, const std::string& styleName);
    
        virtual ~MBVectorTileDecoder();
        
        /**
         * Returns the current style name.
         * @return The current style name.
         */
        const std::string& getCurrentStyleName() const;
        
        /**
         * Select current style by style name. The style must exist in the 
         * style set container specified in the constructor as an xml file.
         * This call will also reset style-related parameters, like geometry and billboard scales of the decoder.
         * @param styleName style to use
         */
        void setCurrentStyle(const std::string& styleName);
    
        /**
         * Sets a style parameter to specified boolean value.
         * The style parameter must be declared in the current style.
         * @param param The parameter to set.
         * @param value The value for the parameter.
         */
        void setStyleParameter(const std::string& param, bool value);
        /**
         * Sets a style parameter to specified integer value.
         * The style parameter must be declared in the current style.
         * @param param The parameter to set.
         * @param value The value for the parameter.
         */
        void setStyleParameter(const std::string& param, long long value);
        /**
         * Sets a style parameter to specified floating point value.
         * The style parameter must be declared in the current style.
         * @param param The parameter to set.
         * @param value The value for the parameter.
         */
        void setStyleParameter(const std::string& param, double value);
        /**
         * Sets a style parameter to specified string value.
         * The style parameter must be declared in the current style.
         * @param param The parameter to set.
         * @param value The value for the parameter.
         */
        void setStyleParameter(const std::string& param, const std::string& value);
    
        virtual Color getBackgroundColor() const;
    
        virtual std::shared_ptr<VT::BitmapPattern> getBackgroundPattern() const;
        
        virtual int getMinZoom() const;
        
        virtual int getMaxZoom() const;
    
        virtual std::shared_ptr<VT::Tile> decodeTile(const VT::TileId& tile, const VT::TileId& targetTile, const std::shared_ptr<TileData>& data) const;
    
    protected:
        void setStyleParameter(const std::string& param, const Mapnik::Value& value);
    
        static cglib::mat3x3<float> calculateTileTransform(const Nuti::VT::TileId& tileId, const Nuti::VT::TileId& targetTileId);
    
        static const int DEFAULT_TILE_SIZE = 256;
        
        std::string _styleName;
        std::shared_ptr<MBVectorTileStyleSet> _styleSet;
        std::shared_ptr<Mapnik::Map> _map;
        std::shared_ptr<std::map<std::string, Mapnik::Value> > _parameterValueMap;
        std::shared_ptr<VT::BitmapPattern> _backgroundPattern;
        std::shared_ptr<MapnikVT::TileSymbolizerContext> _symbolizerContext;
    
        mutable std::mutex _mutex;
    };
        
}

#endif
