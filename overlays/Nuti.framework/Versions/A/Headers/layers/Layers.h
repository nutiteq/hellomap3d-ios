#ifndef LAYERS_H_
#define LAYERS_H_

#include <memory>
#include <mutex>
#include <vector>

namespace Nuti {

class Options;
class Layer;
class MapRenderer;
class CancelableThreadPool;

/**
 * Container for all raster and vector layers of the map view.
 *
 * The order in which layers are added is important for vector elements like Points, Lines
 * and Polygons. For these elements the layer ordering defines their draw order.
 * Other elements like NMLModels and Polygon3Ds are z ordered and are drawn using the depth buffer.
 * For Billboard elements like Markers and Labels, the layer ordering is unimportant, because
 * they will be sorted from back to front and drawn in that order on top of all other vector elements.
 */
class Layers {
public:
	Layers(const std::shared_ptr<CancelableThreadPool>& envelopeThreadPool,
           const std::shared_ptr<CancelableThreadPool>& tileThreadPool,
           const std::weak_ptr<Options>& options);
	virtual ~Layers();

    /**
     * Adds a new layer to the layer stack.
     * @param layer The layer to be added.
     */
	void add(const std::shared_ptr<Layer>& layer);
    /**
     * Removes a layer to the layer stack.
     * @param layer The layer to be removed.
     */
	bool remove(const std::shared_ptr<Layer>& layer);

    /**
     * Returns a list of layers. The layers are in the order in which they were added.
     * @return A vector of all previously added layers.
     */
	std::vector<std::shared_ptr<Layer> > getLayers() const;
    
protected:
    friend class BaseMapView;
    
    void setMapRenderer(const std::shared_ptr<MapRenderer>& mapRenderer);

private:
	std::vector<std::shared_ptr<Layer> > _layers;

    std::shared_ptr<CancelableThreadPool> _envelopeThreadPool;
    std::shared_ptr<CancelableThreadPool> _tileThreadPool;
    std::weak_ptr<Options> _options;
    
    std::weak_ptr<MapRenderer> _mapRenderer;

	mutable std::mutex _mutex;
};

}

#endif
