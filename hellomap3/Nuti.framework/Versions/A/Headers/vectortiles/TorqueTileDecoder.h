/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_TORQUETILEDECODER_H_
#define _NUTI_TORQUETILEDECODER_H_

#include "VectorTileDecoder.h"
#include "MapnikVT/Value.h"

#include <memory>
#include <mutex>
#include <map>
#include <string>

#include <cglib/mat.h>

namespace Nuti {
    namespace MapnikVT {
        class TorqueMap;
        class SymbolizerContext;
    }

    class CartoCSSStyleSet;

    /**
     * A decoder for Torque layer that accepts json-based Torque tiles.
     */
    class TorqueTileDecoder : public VectorTileDecoder {
    public:
        /**
         * Constructs a new TorqueTileDecoder given style.
         * @param styleSet The style set used by decoder.
         */
        TorqueTileDecoder(const std::shared_ptr<CartoCSSStyleSet>& styleSet);
        virtual ~TorqueTileDecoder();

        /**
         * Returns the frame count defined in the Torque style.
         * @return The frame count in the animation.
         */
        int getFrameCount() const;

        /**
         * Returns the current style set used by the decoder.
         * @return The current style set.
         */
        const std::shared_ptr<CartoCSSStyleSet>& getStyleSet() const;
        /**
         * Sets the current style set used by the decoder.
         * @param styleSet The new style set to use.
         */
        void setStyleSet(const std::shared_ptr<CartoCSSStyleSet>& styleSet);

        /**
         * Returns the tile resolution, in pixels. Default is 256.
         * @return The tile resolution in pixels.
         */
        int getResolution() const;
        /**
         * Sets the tile resolution in pixels. Default is 256.
         * @param resolution The new resolution value.
         */
        void setResolution(int resolution);

        virtual Color getBackgroundColor() const;

        virtual std::shared_ptr<const VT::BitmapPattern> getBackgroundPattern() const;

        virtual int getMinZoom() const;

        virtual int getMaxZoom() const;

        virtual std::shared_ptr<TileMap> decodeTile(const VT::TileId& tile, const VT::TileId& targetTile, const std::shared_ptr<TileData>& data) const;

    protected:
        static const int DEFAULT_TILE_SIZE;
        static const int GLYPHMAP_SIZE;

        int _resolution;
        std::shared_ptr<MapnikVT::TorqueMap> _map;
        std::shared_ptr<MapnikVT::SymbolizerContext> _symbolizerContext;
        std::shared_ptr<CartoCSSStyleSet> _styleSet;

        mutable std::mutex _mutex;
    };

}

#endif
