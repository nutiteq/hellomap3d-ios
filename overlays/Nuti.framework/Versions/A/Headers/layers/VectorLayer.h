#ifndef VECTORLAYER_H_
#define VECTORLAYER_H_

#include "components/CancelableTask.h"
#include "datasources/VectorDataSource.h"
#include "core/MapEnvelope.h"
#include "layers/Layer.h"

#include <memory>
#include <unordered_map>

namespace Nuti {

class CullState;

class Billboard;
class BillboardDrawData;
class Label;
class LabelDrawData;
class Line;
class LineDrawData;
class LineStyle;
class Marker;
class MarkerDrawData;
class NMLModel;
class NMLModelDrawData;
class Point;
class PointDrawData;
class Polygon3D;
class Polygon3DDrawData;
class Polygon;
class PolygonDrawData;
class Popup;
class PopupDrawData;

class BillboardRenderer;
class BillboardSorter;
class LineRenderer;
class NMLModelRenderer;
class PointRenderer;
class Polygon3DRenderer;
class PolygonRenderer;

/**
 * A vector layer that loads data using an envelope. Should be used together with corresponding data source.
 */
class VectorLayer : public Layer {
public:
    /**
     * Constructs a VectorLayer object from a data source.
     * @param dataSource The data source from which this layer loads data.
     */
	VectorLayer(const std::shared_ptr<VectorDataSource>& dataSource);
	virtual ~VectorLayer();
    
    /**
     * Returns the vector data source of this vector layer.
     * @return The vector data source that was bound to this vector layer on construction.
     */
    std::shared_ptr<VectorDataSource> getDataSource() const;
    
protected:
    virtual void setComponents(const std::shared_ptr<CancelableThreadPool>& envelopeThreadPool,
                               const std::shared_ptr<CancelableThreadPool>& tileThreadPool,
                               const std::weak_ptr<Options>& options,
                               const std::weak_ptr<MapRenderer>& mapRenderer);
    
    virtual void offsetLayerHorizontally(double offset) ;
    
	virtual void onSurfaceCreated(ShaderManager& shaderManager);
	virtual bool onDrawFrame(float deltaSeconds, BillboardSorter& billboardSorter, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache,
                             const ViewState& viewState);
	virtual void onSurfaceDestroyed();
    
	virtual void calculateRayIntersectedElements(const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir,
                                                 const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;
    
	virtual void registerDataSourceListener();
	virtual void unregisterDataSourceListener();

	virtual void loadData(const std::shared_ptr<CullState>& cullState);

private:
	struct DataSourceListener : public VectorDataSource::OnChangeListener {
		DataSourceListener(VectorLayer& vectorLayer);

		virtual void onElementAdded(const std::shared_ptr<VectorElement>& element);
		virtual void onElementChanged(const std::shared_ptr<VectorElement>& element);
		virtual void onElementRemoved(const std::shared_ptr<VectorElement>& element);
        virtual void onElementsAdded(const std::vector<std::shared_ptr<VectorElement> >& elements);
        virtual void onElementsChanged();
		virtual void onElementsRemoved();

		VectorLayer& _layer;
	};

	class FetchTask : public CancelableTask {
	public:
		FetchTask(const std::weak_ptr<VectorLayer>& layer);
		virtual void run();

	private:
        std::weak_ptr<VectorLayer> _layer;
	};
    
    void updateElement(const std::shared_ptr<VectorElement>& element, bool remove);

	std::shared_ptr<VectorDataSource> _dataSource;
	DataSourceListener _dataSourceListener;

	std::shared_ptr<BillboardRenderer> _billboardRenderer;
	std::shared_ptr<LineRenderer> _lineRenderer;
    std::shared_ptr<NMLModelRenderer> _nmlModelRenderer;
	std::shared_ptr<PointRenderer> _pointRenderer;
    std::shared_ptr<Polygon3DRenderer> _polygon3DRenderer;
	std::shared_ptr<PolygonRenderer> _polygonRenderer;

	std::shared_ptr<CancelableTask> _lastTask;
};

}

#endif
