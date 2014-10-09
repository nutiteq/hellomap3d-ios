#ifndef LAYER_H_
#define LAYER_H_

#include "core/MapRange.h"
#include "renderers/components/CullState.h"
#include "utils/LRUTextureCache.h"

#include <memory>
#include <mutex>
#include <vector>

namespace Nuti {

class BillboardSorter;
class DataSource;
class Layers;
class MapPos;
class MapRenderer;
class MapVec;
class ShaderManager;
class CancelableThreadPool;
class VectorElementClickInfo;
class ViewState;

/**
 * An abstract base class for all layers.
 */
class Layer : public std::enable_shared_from_this<Layer> {
public:
	virtual ~Layer();

    /**
     * Returns the layer task priority of this layer.
     * @return The priority level for the tasks of this layer.
     */
	int getPriority() const;
    /**
     * Sets the layer task priority. Higher priority layers get to load data before
     * lower priority layers. Normal layers and tile layers have seperate task queues and thus 
     * don't compete with each other for task queue access. The default is 0.
     * @param priority The new task priority for this layer, higher values get better access.
     */
	void setPriority(int priority);

    /**
     * Returns the visibility of this layer.
     * @return True if the layer is visible.
     */
	bool isVisible() const;
    /**
     * Sets the visibility of this layer.
     * @param visible The new visibility state of the layer.
     */
	void setVisible(bool visible);

    /**
     * Returns the visible zoom range of this layer.
     * @return The visible zoom range of this layer.
     */
	MapRange getVisibleZoomRange();
    /**
     * Set the visible zoom range for this layer. Current zoom level must be within this range for the layer to be visible.
     * This range is half-open, thus layer is visible if range.min <= ZOOMLEVEL < range.max.
     * @param range new visible zoom range
     */
	void setVisibleZoomRange(const MapRange& range);
	
    /**
     * Updates the layer using new visibility information. This method is periodically called when the map view moves.
     * The visibilty info is saved, so the data can be refreshed later.
     * @param cullState The new visibilty information.
     */
    void update(const std::shared_ptr<CullState>& cullState);
    /**
     * Refreshes the layer using old stored visibility information. This method might be called if some of the layer data
     * changes.
     */
    void refresh();

protected:
	friend class Layers;
    friend class MapRenderer;

	Layer();

	virtual void setComponents(const std::shared_ptr<CancelableThreadPool>& envelopeThreadPool,
                               const std::shared_ptr<CancelableThreadPool>& tileThreadPool,
                               const std::weak_ptr<Options>& options,
                               const std::weak_ptr<MapRenderer>& mapRenderer);

	std::shared_ptr<CullState> getLastCullState() const;

    virtual int getCullDelay() const;

    virtual void loadData(const std::shared_ptr<CullState>& cullState) = 0;
    
    virtual void offsetLayerHorizontally(double offset) = 0;
    
    bool isSurfaceCreated();
	virtual void onSurfaceCreated(ShaderManager& shaderManager);
	virtual bool onDrawFrame(float deltaSeconds, BillboardSorter& BillboardSorter, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache,
                             const ViewState& viewState) = 0;
	virtual void onSurfaceDestroyed();
    
	virtual void calculateRayIntersectedElements(const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir,
                                                 const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const = 0;

	virtual void registerDataSourceListener() = 0;
	virtual void unregisterDataSourceListener() = 0;

	std::shared_ptr<CancelableThreadPool> _envelopeThreadPool;
    std::shared_ptr<CancelableThreadPool> _tileThreadPool;
    std::weak_ptr<Options> _options;
    std::weak_ptr<MapRenderer> _mapRenderer;
    
    std::shared_ptr<CullState> _lastCullState;
    
    int _priority;
    
    bool _visible;
    
	MapRange _visibleZoomRange;

	mutable std::mutex _mutex;

private:
	bool _surfaceCreated;
};

}

#endif
