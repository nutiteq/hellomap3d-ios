#pragma once

#include "TileSymbolizer.h"

namespace Nuti {
	namespace MapnikVT {
		class PolygonSymbolizer : public TileSymbolizer {
		public:
			PolygonSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map) : TileSymbolizer(logger, map) { }

			virtual void setParameter(const std::string& name, const std::string& value) override;

			virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

		protected:
			unsigned int _fill = 0xff808080;
			float _fillOpacity = 1.0f;
		};
	}
}
