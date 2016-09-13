/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_BUILDINGSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_BUILDINGSYMBOLIZER_H_

#include "GeometrySymbolizer.h"

namespace Nuti { namespace MapnikVT {
	class BuildingSymbolizer : public GeometrySymbolizer {
	public:
		explicit BuildingSymbolizer(std::shared_ptr<Logger> logger) : GeometrySymbolizer(std::move(logger)) { }

		virtual void build(const FeatureCollection& featureCollection, const SymbolizerContext& symbolizerContext, const ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
		virtual void bindParameter(const std::string& name, const std::string& value) override;

		const float HEIGHT_SCALE = static_cast<float>(0.5 / 20037508.34);

		VT::Color _fill = VT::Color(0xff808080);
		float _fillOpacity = 1.0f;
		float _height = 0.0f;
	};
} }

#endif
