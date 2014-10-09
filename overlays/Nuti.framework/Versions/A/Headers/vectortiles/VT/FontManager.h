#pragma once

#include "Font.h"

#include <memory>
#include <string>
#include <vector>

namespace Nuti {
	namespace VT {
		class FontManager {
		public:
			struct Parameters {
				const float size;
				const unsigned int color;
				const float haloSize;
				const unsigned int haloColor;
				const std::shared_ptr<Font> baseFont;

				Parameters(float size, unsigned int color, float haloSize, unsigned int haloColor, const std::shared_ptr<Font>& baseFont) : size(size), color(color), haloSize(haloSize), haloColor(haloColor), baseFont(baseFont) { }
			};

			FontManager();
			~FontManager();

			void loadFontData(const std::vector<unsigned char>& data);
			std::shared_ptr<Font> getFont(const std::string& name, const Parameters& parameters) const;
			std::shared_ptr<Font> getNullFont() const;

		private:
			class Impl;

			std::unique_ptr<Impl> _impl;
		};
	}
}
