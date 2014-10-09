#pragma once

#include <cmath>

namespace Nuti {
	namespace Mapnik {
		inline float zoom2ScaleDenominator(float zoom) {
			return 559082264.028f / std::pow(2.0f, zoom);
		}

		inline float scaleDenominator2Zoom(float scaleDenom) {
			return std::log(559082264.028f / scaleDenom) / std::log(2.0f);
		}
	}
}
