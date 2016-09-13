/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_FONT_H_
#define _NUTI_VT_FONT_H_

#include "Bitmap.h"
#include "GlyphMap.h"

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

        using Glyph = GlyphMap::Glyph;
        using GlyphId = GlyphMap::GlyphId;
        using CodePoint = GlyphMap::CodePoint;

		struct Metrics {
			float ascent;
			float descent;
			float height;

			explicit Metrics(float ascent, float descent, float height) : ascent(ascent), descent(descent), height(height) { }
		};

		virtual ~Font() = default;

		virtual const Metrics& getMetrics() const = 0;
		virtual std::vector<Glyph> shapeGlyphs(const std::uint32_t* utf32Text, std::size_t size, bool rtl) const = 0;
		virtual const std::unique_ptr<const Glyph>& loadBitmapGlyph(const std::shared_ptr<const Bitmap>& bitmap) = 0;
		virtual std::shared_ptr<const BitmapPattern> getBitmapPattern() const = 0;
	};
} }

#endif
