/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MBVECTORTILEDECODER_H_
#define _NUTI_MBVECTORTILEDECODER_H_

#include "VectorTileDecoder.h"
#include "MapnikVT/Value.h"

#include <memory>
#include <mutex>
#include <map>
#include <string>

namespace Nuti {
    namespace MapnikVT {
        class Map;
        class SymbolizerContext;
        class Logger;
    }

    class CartoCSSStyleSet;
    class MBVectorTileStyleSet;
    
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
        /**
         * Constructs decoder for MapBox vector tiles based on specified CartoCSS style set.
         * @param cartoCSSStyleSet The CartoCSS style set for the tiles.
         */
        MBVectorTileDecoder(const std::shared_ptr<CartoCSSStyleSet>& cartoCSSStyleSet);
        virtual ~MBVectorTileDecoder();
        
        /**
         * Returns the current style name. Not used for CartoCSS style sets.
         * @return The current style name.
         */
        const std::string& getCurrentStyleName() const;
        
        /**
         * Select current style by style name. Not used for CartoCSS style sets.
         * The style must exist in the style set container specified in the constructor as an xml file.
         * This call will also reset style-related parameters, like geometry and billboard scales of the decoder.
         * @param styleName style to use
         */
        void setCurrentStyle(const std::string& styleName);

        /**
         * Returns the current CartoCSS style set used by the decoder.
         * If decoder uses non-CartoCSS style set, null is returned.
         * @return The current style set.
         */
        const std::shared_ptr<CartoCSSStyleSet>& getCartoCSSStyleSet() const;
        /**
         * Sets the current CartoCSS style set used by the decoder.
         * @param styleSet The new style set to use.
         */
        void setCartoCSSStyleSet(const std::shared_ptr<CartoCSSStyleSet>& styleSet);
    
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

        /**
         * Set tile buffering. This is intended for special tile sources like MapZen.
         * @param buffer The amount of buffering to use. It is based on normalized tile coordinates (tile width=1.0), so 1.0/64.0 is a sensible value. The default is 0.
         */
        void setBuffering(float buffer);

        virtual Color getBackgroundColor() const;
    
        virtual std::shared_ptr<const VT::BitmapPattern> getBackgroundPattern() const;
        
        virtual int getMinZoom() const;
        
        virtual int getMaxZoom() const;
    
        virtual std::shared_ptr<TileMap> decodeTile(const VT::TileId& tile, const VT::TileId& targetTile, const std::shared_ptr<TileData>& data) const;
    
    protected:
        void setStyleParameter(const std::string& param, const MapnikVT::Value& value);
        void loadMapnikMap(const std::vector<unsigned char>& styleData);
        void loadCartoCSSMap(const std::string& fileName, const std::vector<unsigned char>& styleData);
        void loadCartoCSSMap(const std::shared_ptr<CartoCSSStyleSet>& styleSet);
    
        static const int DEFAULT_TILE_SIZE;
        static const int STROKEMAP_SIZE;
        static const int GLYPHMAP_SIZE;
        
        float _buffer;
        std::string _styleName;
        std::shared_ptr<MBVectorTileStyleSet> _mbStyleSet;
        std::shared_ptr<CartoCSSStyleSet> _cartoCSSStyleSet;
        std::shared_ptr<MapnikVT::Map> _map;
        std::shared_ptr<MapnikVT::Logger> _logger;
        std::shared_ptr<std::map<std::string, MapnikVT::Value> > _parameterValueMap;
        std::shared_ptr<const VT::BitmapPattern> _backgroundPattern;
        std::shared_ptr<MapnikVT::SymbolizerContext> _symbolizerContext;
    
        mutable std::mutex _mutex;
    };
        
}

#endif
