/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_FONT_H_
#define _NUTI_VT_FONT_H_

#include "Bitmap.h"

#include <memory>
#include <string>
#include <cstdint>

#include <cglib/vec.h>

namespace Nuti { namespace VT {
	class Font {
	public:
		enum {
			SPACE_CODEPOINT   = 0xffff0000,
			CR_CODEPOINT      = 0xffff0001,
			BITMAP_CODEPOINTS = 0xffff0002
		};
		
		struct Glyph {
			unsigned int codepoint;
			int x;
			int y;
			int width;
			int height;
			cglib::vec2<float> size;
			cglib::vec2<float> offset;
			cglib::vec2<float> advance;

			Glyph(unsigned int codepoint, int x, int y, int width, int height, const cglib::vec2<float>& size, const cglib::vec2<float>& offset, const cglib::vec2<float>& advance) : codepoint(codepoint), x(x), y(y), width(width), height(height), size(size), offset(offset), advance(advance) { }
		};

		struct Metrics {
			float ascent;
			float descent;
			float height;

			Metrics(float ascent, float descent, float height) : ascent(ascent), descent(descent), height(height) { }
		};

		virtual ~Font() = default;

		virtual const Metrics& getMetrics() const = 0;
		virtual std::vector<Glyph> shapeGlyphs(const std::uint32_t* utf32Text, std::size_t size, bool rtl) const = 0;
		virtual const std::unique_ptr<Glyph>& loadBitmapGlyph(const std::shared_ptr<Bitmap>& bitmap) = 0;
		virtual std::shared_ptr<Bitmap> getBitmap() const = 0;
	};
} }

#endif
