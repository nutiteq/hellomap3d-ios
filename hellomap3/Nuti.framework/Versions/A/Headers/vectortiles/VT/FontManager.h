/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_FONTMANAGER_H_
#define _NUTI_VT_FONTMANAGER_H_

#include "Color.h"
#include "Font.h"

#include <memory>
#include <string>
#include <vector>

namespace Nuti { namespace VT {
	class FontManager {
	public:
		struct Parameters {
			const float size;
			const Color color;
			const float haloSize;
			const Color haloColor;
			const std::shared_ptr<Font> baseFont;

			explicit Parameters(float size, const Color& color, float haloSize, const Color& haloColor, std::shared_ptr<Font> baseFont) : size(size), color(color), haloSize(haloSize), haloColor(haloColor), baseFont(std::move(baseFont)) { }
		};

		explicit FontManager(int maxGlyphMapWidth, int maxGlyphMapHeight);
		virtual ~FontManager();

		void loadFontData(const std::vector<unsigned char>& data);
		std::shared_ptr<Font> getFont(const std::string& name, const Parameters& parameters) const;
		std::shared_ptr<Font> getNullFont() const;

	private:
		class Impl;

		std::unique_ptr<Impl> _impl;
	};
} }

#endif
