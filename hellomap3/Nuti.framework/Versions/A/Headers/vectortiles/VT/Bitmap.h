#pragma once

#include <cstdint>
#include <vector>
#include <memory>

namespace Nuti {
	namespace VT {
		struct Bitmap {
			const int width;
			const int height;
			const std::vector<std::uint32_t> data;

			Bitmap(int width, int height, std::vector<std::uint32_t>&& data) : width(width), height(height), data(std::move(data)) { }
		};

		struct BitmapPattern {
			const float widthScale;
			const float heightScale;
			const std::shared_ptr<const Bitmap> bitmap;

			BitmapPattern(float widthScale, float heightScale, const std::shared_ptr<Bitmap>& bitmap) : widthScale(widthScale), heightScale(heightScale), bitmap(bitmap) { }
		};
	}
}
