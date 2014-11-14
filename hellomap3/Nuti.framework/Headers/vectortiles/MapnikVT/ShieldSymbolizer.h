/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_SHIELDSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_SHIELDSYMBOLIZER_H_

#include "TextSymbolizer.h"

namespace Nuti { namespace MapnikVT {
	class ShieldSymbolizer : public TextSymbolizer {
	public:
		ShieldSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map, const std::shared_ptr<Mapnik::Expression>& textExpression, const std::vector<std::shared_ptr<Mapnik::FontSet>>& fontSets) : TextSymbolizer(logger, map, textExpression, fontSets) { }

		virtual void setParameter(const std::string& name, const std::string& value) override;

		virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

	protected:
		std::string _file;
		std::string _unlockImage = "false";
		float _shieldDx = 0.0f;
		float _shieldDy = 0.0f;
	};
} }

#endif
