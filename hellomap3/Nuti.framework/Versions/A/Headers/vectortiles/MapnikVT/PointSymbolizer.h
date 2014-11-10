#pragma once

#include "TileSymbolizer.h"

#include <memory>

namespace Nuti {
	namespace MapnikVT {
		class PointSymbolizer : public TileSymbolizer {
		public:
			PointSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map) : TileSymbolizer(logger, map) { }

			virtual void setParameter(const std::string& name, const std::string& value) override;

			virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

		protected:
			static std::shared_ptr<VT::Bitmap> createRectangleBitmap(int size);

			const int DEFAULT_POINT_PRIORITY = 1;
			const int CUSTOM_POINT_PRIORITY = 100;
			const int RECTANGLE_SIZE = 4;

			std::string _file;
			unsigned int _fill = 0xff000000;
			float _opacity = 1.0f;
			float _width = 10;
			float _height = 10;
			bool _allowOverlap = false;
			bool _ignorePlacement = false;
		};
	}
}
