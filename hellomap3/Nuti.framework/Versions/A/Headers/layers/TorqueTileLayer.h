/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_TORQUETILELAYER_H_
#define _NUTI_TORQUETILELAYER_H_

#include <memory>

#include "layers/VectorTileLayer.h"

namespace Nuti {
    class TorqueTileDecoder;

    /**
     * A vector tile layer for rendering time-based animated point clouds.
     */
    class TorqueTileLayer : public VectorTileLayer {
    public:
        TorqueTileLayer(const std::shared_ptr<TileDataSource>& dataSource, const std::shared_ptr<TorqueTileDecoder>& decoder);
        virtual ~TorqueTileLayer();

        /**
         * Returns the frame count.
         * @return Frame count in the layer.
         */
        int getFrameCount() const;
        /**
         * Returns the current frame number.
         * @return The current frame number.
         */
        int getFrameNr() const;
        /**
         * Sets the frame number.
         * @param frameNr The frame number to display.
         */
        void setFrameNr(int frameNr);
    };
}

#endif
