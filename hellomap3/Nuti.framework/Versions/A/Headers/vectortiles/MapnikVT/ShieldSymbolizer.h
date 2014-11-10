#pragma once

#include "TextSymbolizer.h"

namespace Nuti {
	namespace MapnikVT {
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
	}
}
