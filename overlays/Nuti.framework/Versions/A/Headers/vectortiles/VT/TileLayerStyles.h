#pragma once

#include "Bitmap.h"
#include "Font.h"
#include "TextFormatter.h"

#include <memory>

#include <cglib/vec.h>

namespace Nuti {
	namespace VT {
		enum class LabelOrientation {
			BILLBOARD, POINT, LINE
		};

		enum class LineJoinMode {
			NONE, BEVEL, MITER, ROUND
		};

		enum class LineCapMode {
			NONE, SQUARE, ROUND
		};

		struct LineStyle {
			LineJoinMode joinMode;
			LineCapMode capMode;
			unsigned int color;
			float width;
			std::shared_ptr<BitmapPattern> pattern;

			LineStyle(LineJoinMode joinMode, LineCapMode capMode, unsigned int color, float width, const std::shared_ptr<BitmapPattern>& pattern) : joinMode(joinMode), capMode(capMode), color(color), width(width), pattern(pattern) { }
		};

		struct PolygonStyle {
			unsigned int color;
			float patternScale;
			std::shared_ptr<BitmapPattern> pattern;

			PolygonStyle(unsigned int color, float patternScale, const std::shared_ptr<BitmapPattern>& pattern) : color(color), patternScale(patternScale), pattern(pattern) { }
		};

		struct Polygon3DStyle {
			unsigned int color;

			Polygon3DStyle(unsigned int color) : color(color) { }
		};

		struct BitmapLabelStyle {
			LabelOrientation placement;
			unsigned int color;
			float scale;
			std::shared_ptr<Font> font;
			std::shared_ptr<Bitmap> bitmap;

			BitmapLabelStyle(LabelOrientation placement, unsigned int color, float scale, const std::shared_ptr<Font>& font, const std::shared_ptr<Bitmap>& bitmap) : placement(placement), color(color), scale(scale), font(font), bitmap(bitmap) { }
		};

		struct TextLabelStyle {
			LabelOrientation placement;
			float scale;
			TextFormatter::Options formatterOptions;
			std::shared_ptr<Font> font;
			float backgroundScale;
			std::shared_ptr<Bitmap> backgroundBitmap;

			TextLabelStyle(LabelOrientation placement, float scale, const TextFormatter::Options& formatterOptions, const std::shared_ptr<Font>& font, float backgroundScale, const std::shared_ptr<Bitmap>& backgroundBitmap) : placement(placement), scale(scale), formatterOptions(formatterOptions), font(font), backgroundScale(backgroundScale), backgroundBitmap(backgroundBitmap) { }
		};
	}
}
