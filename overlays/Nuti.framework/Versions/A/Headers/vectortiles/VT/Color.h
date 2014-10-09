#pragma once

#include <cglib/vec.h>
#include <cmath>

namespace Nuti {
	namespace VT {
		inline cglib::vec4<float> normalizeColor(unsigned int color) {
			cglib::vec4<float> normalizedColor;
			normalizedColor(2) = static_cast<float>((color >>  0) & 255);
			normalizedColor(1) = static_cast<float>((color >>  8) & 255);
			normalizedColor(0) = static_cast<float>((color >> 16) & 255);
			normalizedColor(3) = static_cast<float>((color >> 24) & 255);
			return normalizedColor * (1.0f / 255.0f);
		}

		inline unsigned int denormalizeColor(const cglib::vec4<float>& normalizedColor) {
			unsigned int color = 0;
			color |= static_cast<int>(normalizedColor(2) * 255.0f) << 0;
			color |= static_cast<int>(normalizedColor(1) * 255.0f) << 8;
			color |= static_cast<int>(normalizedColor(0) * 255.0f) << 16;
			color |= static_cast<int>(normalizedColor(3) * 255.0f) << 24;
			return color;
		}

		inline cglib::vec4<float> correctGamma(const cglib::vec4<float>& normalizedColor, float gamma) {
			cglib::vec4<float> correctedColor;
			for (int i = 0; i < 4; i++) {
				correctedColor(i) = std::pow(normalizedColor(i), gamma);
			}
			return correctedColor;
		}
	}
}
