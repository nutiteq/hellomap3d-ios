#pragma once

#include "TileSymbolizer.h"

namespace Nuti {
	namespace MapnikVT {
		class BuildingSymbolizer : public TileSymbolizer {
		public:
			BuildingSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map) : TileSymbolizer(logger, map) { }

			virtual void setParameter(const std::string& name, const std::string& value) override;

			virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

		protected:
			const float HEIGHT_SCALE = static_cast<float>(0.5 / 20037508.34);

			unsigned int _fill = 0xff808080;
			float _fillOpacity = 1.0f;
			float _height = 0.0f;
		};
	}
}
