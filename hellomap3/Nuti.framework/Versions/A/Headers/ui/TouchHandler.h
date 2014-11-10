#ifndef TOUCHHANDLER_H_
#define TOUCHHANDLER_H_

#include "ClickHandlerWorker.h"
#include "core/MapPos.h"
#include "core/MapVec.h"

#include <chrono>
#include <memory>
#include <thread>
#include <vector>

namespace Nuti {

class Options;
class MapRenderer;

class TouchHandler : public std::enable_shared_from_this<TouchHandler> {
public:
	enum {
		ACTION_POINTER_1_DOWN = 0,
		ACTION_POINTER_2_DOWN = 1,
		ACTION_MOVE = 2,
		ACTION_CANCEL = 3,
		ACTION_POINTER_1_UP = 4,
		ACTION_POINTER_2_UP = 5
	};

	TouchHandler(const std::shared_ptr<MapRenderer>& mapRenderer, const std::shared_ptr<Options>& options);
    void init();
	virtual ~TouchHandler();
    void deinit();

	void onTouchEvent(int action, const MapPos& screenPos1, const MapPos& screenPos2);

	void click(const MapPos& screenPos) const;
	void longClick(const MapPos& screenPos);
	void doubleClick(const MapPos& screenPos) const;
	void dualClick(const MapPos& screenPos1, const MapPos& screenPos2) const;
	void startSinglePointer(const MapPos& screenPos);
	void startDualPointer(const MapPos& screenPos1, const MapPos& screenPos2);
    
protected:
    friend class BaseMapView;
    
    void setMapRenderer(std::shared_ptr<MapRenderer> mapRenderer);

private:
	double calculateRotatingScalingFactor(const MapVec& deltaPos1, const MapVec& deltaPos2);

	void singlePointerPan(const MapPos& screenPos);
	void dualPointerGuess(const MapPos& screenPos1, const MapPos& screenPos2);
	void dualPointerTilt(const MapPos& screenPos);
	void dualPointerPan(const MapPos& screenPos1, const MapPos& screenPos2, bool rotate, bool scale);

	static const int SINGLE_POINTER_CLICK_GUESS = 0;
	static const int DUAL_POINTER_CLICK_GUESS = 1;
	static const int SINGLE_POINTER_PAN = 2;
	static const int DUAL_POINTER_GUESS = 3;
	static const int DUAL_POINTER_TILT = 4;
	static const int DUAL_POINTER_ROTATE = 5;
	static const int DUAL_POINTER_SCALE = 6;
	static const int DUAL_POINTER_FREE = 7;


	static const float GUESS_MAX_DELTA_Y_INCHES;
	static const float GUESS_MIN_SWIPE_LENGTH_SAME_INCHES;
	static const float GUESS_MIN_SWIPE_LENGTH_OPPOSITE_INCHES;

	// Determines whether to choose view angle or some other pointer mode
	static const float GUESS_SWIPE_ABS_COS_THRESHOLD;

	// Determines when to switch between scalign and rotating when google style
	// panning is enabled
	static const float ROTATION_SCALING_FACTOR_THRESHOLD;

	// Determines how the finger sliding distance will be converted to tilt angle
	static const float INCHES_TO_VIEW_ANGLE;
    
    // Determines how long it takes to cancel kinetic zoom and rotation after one
    // pointer is lifted but the other one is not
    static const float DUAL_KINETIC_HOLD_DURATION_S;

	// Map panning type, 0 = fast, accurate (finger stays exactly in the same
	// place), 1 = slow, inaccurate
	static const float PANNING_FACTOR;

	int _panningMode;

	MapPos _prevScreenPos1;
	MapPos _prevScreenPos2;

	MapVec _swipe1;
	MapVec _swipe2;

	bool _noDualPointerYet;
    std::chrono::time_point<std::chrono::system_clock> _dualPointerReleaseTime;

    std::shared_ptr<ClickHandlerWorker> _clickHandlerWorker;
	std::thread _clickHandlerThread;

    std::shared_ptr<Options> _options;
	std::shared_ptr<MapRenderer> _mapRenderer;

	mutable std::mutex _mutex;
};

}

#endif
