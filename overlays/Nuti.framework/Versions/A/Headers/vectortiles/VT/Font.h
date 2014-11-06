#pragma once

#include "Bitmap.h"

#include <memory>
#include <string>

#include <cglib/vec.h>

namespace Nuti {
	namespace VT {
		class Font {
		public:
			struct Glyph {
				unsigned int code;
				unsigned int id;
				int x;
				int y;
				int width;
				int height;
				cglib::vec2<float> size;
				cglib::vec2<float> offset;
				cglib::vec2<float> advance;

				Glyph(unsigned int code, unsigned int id, int x, int y, int width, int height, const cglib::vec2<float>& size, const cglib::vec2<float>& offset, const cglib::vec2<float>& advance) : code(code), id(id), x(x), y(y), width(width), height(height), size(size), offset(offset), advance(advance) { }
			};

			struct Metrics {
				float ascent;
				float descent;
				float height;

				Metrics(float ascent, float descent, float height) : ascent(ascent), descent(descent), height(height) { }
			};

			virtual ~Font() = default;

			virtual const Metrics& getMetrics() const = 0;
			virtual const std::unique_ptr<Glyph>& getGlyph(unsigned int code) const = 0;
			virtual unsigned int loadBitmapGlyph(const std::shared_ptr<Bitmap>& bitmap) = 0;
			virtual std::shared_ptr<Bitmap> getBitmap() const = 0;
		};
	}
}
