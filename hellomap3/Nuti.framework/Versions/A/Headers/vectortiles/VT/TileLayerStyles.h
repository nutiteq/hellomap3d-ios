/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_TILELAYERSTYLES_H_
#define _NUTI_VT_TILELAYERSTYLES_H_

#include "Bitmap.h"
#include "Font.h"
#include "StrokeSet.h"
#include "TextFormatter.h"

#include <memory>

#include <boost/optional.hpp>

#include <cglib/vec.h>
#include <cglib/mat.h>

namespace Nuti { namespace VT {
	enum class LabelOrientation {
		BILLBOARD2D, BILLBOARD3D, POINT, LINE
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
		std::shared_ptr<BitmapPattern> strokePattern;
		std::shared_ptr<StrokeSet> strokeSet;
		boost::optional<cglib::mat3x3<float>> transform;

        LineStyle(LineJoinMode joinMode, LineCapMode capMode, unsigned int color, float width, std::shared_ptr<BitmapPattern> strokePattern, std::shared_ptr<StrokeSet> strokeSet, const boost::optional<cglib::mat3x3<float>>& transform) : joinMode(joinMode), capMode(capMode), color(color), width(width), strokePattern(std::move(strokePattern)), strokeSet(std::move(strokeSet)), transform(transform) { }
	};

	struct PolygonStyle {
		unsigned int color;
		std::shared_ptr<BitmapPattern> pattern;
		boost::optional<cglib::mat3x3<float>> transform;

        PolygonStyle(unsigned int color, std::shared_ptr<BitmapPattern> pattern, const boost::optional<cglib::mat3x3<float>>& transform) : color(color), pattern(std::move(pattern)), transform(transform) { }
	};

	struct Polygon3DStyle {
		unsigned int color;
		boost::optional<cglib::mat3x3<float>> transform;

		Polygon3DStyle(unsigned int color, const boost::optional<cglib::mat3x3<float>>& transform) : color(color), transform(transform) { }
	};

	struct BitmapLabelStyle {
		LabelOrientation placement;
		unsigned int color;
		std::shared_ptr<Font> font;
		std::shared_ptr<Bitmap> bitmap;
		cglib::mat3x3<float> transform;

        BitmapLabelStyle(LabelOrientation placement, unsigned int color, std::shared_ptr<Font> font, std::shared_ptr<Bitmap> bitmap, const cglib::mat3x3<float>& transform) : placement(placement), color(color), font(std::move(font)), bitmap(std::move(bitmap)), transform(transform) { }
	};

	struct TextLabelStyle {
		LabelOrientation placement;
		TextFormatter::Options formatterOptions;
		std::shared_ptr<Font> font;
		float angle;
		float backgroundScale;
		cglib::vec2<float> backgroundOffset;
		std::shared_ptr<Bitmap> backgroundBitmap;

        TextLabelStyle(LabelOrientation placement, const TextFormatter::Options& formatterOptions, std::shared_ptr<Font> font, float angle, float backgroundScale, const cglib::vec2<float>& backgroundOffset, std::shared_ptr<Bitmap> backgroundBitmap) : placement(placement), formatterOptions(formatterOptions), font(std::move(font)), angle(angle), backgroundScale(backgroundScale), backgroundOffset(backgroundOffset), backgroundBitmap(std::move(backgroundBitmap)) { }
	};
} }

#endif
