/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_BITMAP_H_
#define _NUTI_VT_BITMAP_H_

#include <cstdint>
#include <vector>
#include <memory>

namespace Nuti { namespace VT {
	struct Bitmap {
		const int width;
		const int height;
		const std::vector<std::uint32_t> data;

		explicit Bitmap(int width, int height, std::vector<std::uint32_t> data) : width(width), height(height), data(std::move(data)) { }
	};

	struct BitmapPattern {
		const float widthScale;
		const float heightScale;
		const std::shared_ptr<const Bitmap> bitmap;

		explicit BitmapPattern(float widthScale, float heightScale, std::shared_ptr<Bitmap> bitmap) : widthScale(widthScale), heightScale(heightScale), bitmap(std::move(bitmap)) { }
	};
} }

#endif
