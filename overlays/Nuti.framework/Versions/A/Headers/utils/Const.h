#ifndef CONST_H_
#define CONST_H_

namespace Nuti {

class Const {
public:
	// Predefined PI value
	static const double PI;

	// Values used for converting between degrees and radians
	static const double DEG_TO_RAD;
	static const double RAD_TO_DEG;

	// World size. World bounds are from left -HALF_WORLD_SIZE to right +HALF_WORLD_SIZE
	// and from top +HALF_WORLD_SIZE to bottom -HALF_WORLD_SIZE
	static const int WORLD_SIZE = 1000000;
	static const float HALF_WORLD_SIZE;

	// Maximum supported zoom level
	static const int MAX_SUPPORTED_ZOOM_LEVEL;
	// Fractional added to floating point zoom level before truncating.
	static const float DISCRETE_ZOOM_LEVEL_BIAS;
	// Maximum range for all possible tile ids for a single raster layer
	static const long long TILE_ID_OFFSET;

	// Min and max supported tilt angles
	static const int MIN_SUPPORTED_TILT_ANGLE = 30;
    
    // If device dpi = UNSCALED_DPI then 1 dp = 1 px
    static const int UNSCALED_DPI = 160;

	// Maximum building height, taller buildings will get clipped, if the camera
	// gets lower than the acutal building height, then it will get clipped anyway
	// for world map: Const.UNIT_SIZE / 16667. For SF map this looks usable: Const.UNIT_SIZE / 833
	static const float MAX_HEIGHT;
	// Minimum near plane distance, used to avoid visual artifacts on large zoom levels
	static const float MIN_NEAR;
	// Maximum near plane distance
	static const int MAX_NEAR = 100;

	// Size limit (in bytes) for style texture cache
	static const int STYLE_TEXTURE_CACHE_SIZE = 1024 * 1024 * 15;

	static const float LOGE_2;
};

}

#endif
