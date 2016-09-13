/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_LINESYMBOLIZER_H_
#define _NUTI_MAPNIKVT_LINESYMBOLIZER_H_

#include "GeometrySymbolizer.h"

namespace Nuti { namespace MapnikVT {
	class LineSymbolizer : public GeometrySymbolizer {
	public:
        explicit LineSymbolizer(std::shared_ptr<Logger> logger) : GeometrySymbolizer(std::move(logger)) { }

		virtual void build(const FeatureCollection& featureCollection, const SymbolizerContext& symbolizerContext, const ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
        virtual void bindParameter(const std::string& name, const std::string& value) override;

        static std::shared_ptr<VT::BitmapPattern> createDashBitmapPattern(const std::vector<float>& strokeDashArray);

		enum { MIN_SUPERSAMPLING_FACTOR = 2, MAX_SUPERSAMPLING_FACTOR = 16 };

		VT::Color _stroke = VT::Color(0xff000000);
		float _strokeWidth = 1.0f;
		float _strokeOpacity = 1.0f;
		std::string _strokeLinejoin = "miter";
		std::string _strokeLinecap = "butt";
		std::string _strokeDashArray;
	};
} }

#endif
