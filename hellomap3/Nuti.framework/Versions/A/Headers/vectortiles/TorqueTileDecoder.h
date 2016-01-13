#ifndef _NUTI_TORQUETILEDECODER_H_
#define _NUTI_TORQUETILEDECODER_H_

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

    class CartoCSSStyle;

    class TorqueTileDecoder : public VectorTileDecoder {
    public:
        TorqueTileDecoder(const std::shared_ptr<CartoCSSStyle>& style);

        virtual ~TorqueTileDecoder();

        const std::shared_ptr<CartoCSSStyle>& getStyle() const;

        void setStyle(const const std::shared_ptr<CartoCSSStyle>& style);

        // TODO: use boost variant for both
        virtual Color getBackgroundColor() const;

        virtual std::shared_ptr<VT::BitmapPattern> getBackgroundPattern() const;

        virtual int getMinZoom() const;

        virtual int getMaxZoom() const;

        // TODO: Torque-specific attributes for animation

        virtual std::shared_ptr<VT::Tile> decodeTile(const VT::TileId& tile, const VT::TileId& targetTile, const std::shared_ptr<TileData>& data) const;

    protected:
        static const int DEFAULT_TILE_SIZE = 256;

        std::shared_ptr<Mapnik::Map> _map;
        std::shared_ptr<VT::BitmapPattern> _backgroundPattern;
        std::shared_ptr<MapnikVT::TileSymbolizerContext> _symbolizerContext;

        mutable std::mutex _mutex;
    };

}

#endif
