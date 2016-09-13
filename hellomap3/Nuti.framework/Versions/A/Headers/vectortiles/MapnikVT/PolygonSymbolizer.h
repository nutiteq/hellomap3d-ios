/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_POLYGONSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_POLYGONSYMBOLIZER_H_

#include "GeometrySymbolizer.h"

namespace Nuti { namespace MapnikVT {
	class PolygonSymbolizer : public GeometrySymbolizer {
	public:
        explicit PolygonSymbolizer(std::shared_ptr<Logger> logger) : GeometrySymbolizer(std::move(logger)) { }

		virtual void build(const FeatureCollection& featureCollection, const SymbolizerContext& symbolizerContext, const ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
        virtual void bindParameter(const std::string& name, const std::string& value) override;

        VT::Color _fill = VT::Color(0xff808080);
		float _fillOpacity = 1.0f;
	};
} }

#endif
