/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_TEXTFORMATTER_H_
#define _NUTI_VT_TEXTFORMATTER_H_

#include "Font.h"

#include <memory>
#include <string>
#include <vector>

namespace Nuti { namespace VT {
	class TextFormatter {
	public:
		struct Options {
			cglib::vec2<float> alignment;
			cglib::vec2<float> offset;
			bool wrapBefore;
			float wrapWidth;
			float characterSpacing;
			float lineSpacing;

			Options(const cglib::vec2<float>& alignment, const cglib::vec2<float>& offset, bool wrapBefore, float wrapWidth, float characterSpacing, float lineSpacing) : alignment(alignment), offset(offset), wrapBefore(wrapBefore), wrapWidth(wrapWidth), characterSpacing(characterSpacing), lineSpacing(lineSpacing) { }
		};

		TextFormatter(const std::shared_ptr<Font>& font);

		std::vector<Font::Glyph> format(const std::string& text, const Options& options) const;

	private:
		std::vector<std::vector<unsigned int>> splitLines(const std::string& text, const Options& options) const;

		std::shared_ptr<Font> _font;
	};
} }

#endif
