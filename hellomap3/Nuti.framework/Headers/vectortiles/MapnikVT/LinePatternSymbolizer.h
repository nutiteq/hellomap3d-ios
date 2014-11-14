/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_LINEPATTERNSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_LINEPATTERNSYMBOLIZER_H_

#include "TileSymbolizer.h"

namespace Nuti { namespace MapnikVT {
	class LinePatternSymbolizer : public TileSymbolizer {
	public:
		LinePatternSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map) : TileSymbolizer(logger, map) { }

		virtual void setParameter(const std::string& name, const std::string& value) override;

		virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
		std::string _file;
		unsigned int _fill = 0xffffffff;
		float _opacity = 1.0f;
	};
} }

#endif
