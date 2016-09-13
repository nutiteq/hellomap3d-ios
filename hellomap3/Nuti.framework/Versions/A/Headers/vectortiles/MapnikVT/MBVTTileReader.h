/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_MBVTTILEREADER_H_
#define _NUTI_MAPNIKVT_MBVTTILEREADER_H_

#include "TileReader.h"
#include "Map.h"

namespace Nuti { namespace MapnikVT {
    class MBVTFeatureDecoder;
	
    class MBVTTileReader : public TileReader {
	public:
        explicit MBVTTileReader(std::shared_ptr<Map> map, const SymbolizerContext& symbolizerContext, const MBVTFeatureDecoder& featureDecoder) : TileReader(std::move(map), symbolizerContext), _featureDecoder(featureDecoder) { }

    protected:
        virtual std::shared_ptr<FeatureDecoder::FeatureIterator> createFeatureIterator(const std::shared_ptr<Layer>& layer, const std::shared_ptr<Style>& style, const ExpressionContext& exprContext) const override;

        const MBVTFeatureDecoder& _featureDecoder;
	};
} }

#endif
