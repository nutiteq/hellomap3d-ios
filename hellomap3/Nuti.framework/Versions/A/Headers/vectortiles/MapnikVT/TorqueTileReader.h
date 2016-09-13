/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_TORQUETILEREADER_H_
#define _NUTI_MAPNIKVT_TORQUETILEREADER_H_

#include "TileReader.h"
#include "TorqueMap.h"

namespace Nuti { namespace MapnikVT {
    class TorqueFeatureDecoder;
	
    class TorqueTileReader : public TileReader {
	public:
        explicit TorqueTileReader(std::shared_ptr<TorqueMap> map, int frame, bool loop, const SymbolizerContext& symbolizerContext, const TorqueFeatureDecoder& featureDecoder) : TileReader(std::move(map), symbolizerContext), _frame(frame), _loop(loop), _featureDecoder(featureDecoder) { }

    protected:
        virtual std::shared_ptr<FeatureDecoder::FeatureIterator> createFeatureIterator(const std::shared_ptr<Layer>& layer, const std::shared_ptr<Style>& style, const ExpressionContext& exprContext) const override;

    private:
        const int _frame;
        const bool _loop;
        const TorqueFeatureDecoder& _featureDecoder;
	};
} }

#endif
