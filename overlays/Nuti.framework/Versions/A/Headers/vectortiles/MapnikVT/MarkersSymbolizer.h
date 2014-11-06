#pragma once

#include "TileSymbolizer.h"

#include <memory>

namespace Nuti {
	namespace MapnikVT {
		class MarkersSymbolizer : public TileSymbolizer {
		public:
			MarkersSymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map) : TileSymbolizer(logger, map) { }

			virtual void setParameter(const std::string& name, const std::string& value) override;

			virtual void build(const Feature& feature, const TileSymbolizerContext& symbolizerContext, const Mapnik::ExpressionContext& exprContext, VT::TileLayerBuilder& layerBuilder) override;

		protected:
			static std::shared_ptr<VT::Bitmap> makeEllipseBitmap(int width, int height);
			static std::shared_ptr<VT::Bitmap> makeArrowBitmap(int width, int height);

			const int DEFAULT_MARKER_PRIORITY = 1;
			const int CUSTOM_MARKER_PRIORITY = 100;
			const int DEFAULT_MARKER_SIZE = 10;
			const int DEFAULT_CIRCLE_SIZE = 10;
			const int DEFAULT_ARROW_WIDTH = 28, DEFAULT_ARROW_HEIGHT = 14;

			std::string _file;
			std::string _placement = "point";
			std::string _markerType;
			unsigned int _fill = 0xff0000ff;
			float _opacity = 1.0f;
			float _width = -1;
			float _height = -1;
			bool _allowOverlap = false;
			bool _ignorePlacement = false;
		};
	}
}
