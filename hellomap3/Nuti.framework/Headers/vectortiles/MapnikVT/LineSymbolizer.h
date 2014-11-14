/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_LINESYMBOLIZER_H_
#define _NUTI_MAPNIKVT_LINESYMBOLIZER_H_

#include "TileSymbolizer.h"

#include <memory>

namespace Nuti { namespace MapnikVT {
	class LineSymbolizer : public TileSymbolizer {
	public:
		LineSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map) : TileSymbolizer(logger, map) { }

		virtual void setParameter(const std::string& name, const std::string& value) override;

		virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
		static std::shared_ptr<VT::BitmapPattern> createDashBitmapPattern(int dashSize, const std::string& value);

		const int DASH_SIZE = 16;

		unsigned int _stroke = 0xff000000;
		float _strokeWidth = 1.0f;
		float _strokeOpacity = 1.0f;
		std::string _strokeLinejoin = "miter";
		std::string _strokeLinecap = "butt";
		std::string _strokeDasharray;
	};
} }

#endif
