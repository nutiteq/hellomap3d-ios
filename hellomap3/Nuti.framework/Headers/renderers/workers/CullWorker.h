#ifndef CULLWORKER_H_
#define CULLWORKER_H_

#include "components/ThreadWorker.h"
#include "core/MapEnvelope.h"
#include "graphics/Frustum.h"
#include "renderers/components/CullState.h"

#include <chrono>
#include <condition_variable>
#include <map>
#include <memory>
#include <thread>
#include <vector>

namespace Nuti {

class EnvelopeLayer;
class Layer;
class MapRenderer;
class Options;

class CullWorker : public ThreadWorker {
public:
	CullWorker();
	virtual ~CullWorker();
    
    void setComponents(const std::weak_ptr<MapRenderer>& mapRenderer, const std::shared_ptr<CullWorker>& cullWorker);

	void init(const std::shared_ptr<Layer>& layer, int delayTime);
    
	void stop();

	void operator()();

private:
	typedef std::map<std::shared_ptr<Layer>, std::chrono::time_point<std::chrono::system_clock> > LayerWakeupMap;

	static const float PRELOADING_FRUSTUM_SCALE;
	static const float PRELOADING_MIN_TILT_ANGLE;
	static const float PRELOADING_TILT_COEF;
    
    void run();

	void calculateCullState();
	void calculateEnvelope();
	void updateLayers();

	LayerWakeupMap _layerWakeupMap;
	mutable std::mutex _layerWakeupMapMutex;

    std::vector<std::shared_ptr<Layer> > _layers;
    
    bool _firstCull;
    
    MapEnvelope _envelope;
    
    Frustum _preloadingFrustum;
    
    MapPos _preloadingCameraPos;
    
	ViewState _viewState;

    std::weak_ptr<MapRenderer> _mapRenderer;
    std::shared_ptr<CullWorker> _worker;

	bool _stop;
	std::condition_variable _condition;
	mutable std::mutex _mutex;
};

}

#endif
