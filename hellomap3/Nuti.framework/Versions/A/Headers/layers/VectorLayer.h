/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VECTORLAYER_H_
#define _NUTI_VECTORLAYER_H_

#include "components/CancelableTask.h"
#include "components/DirectorPtr.h"
#include "datasources/VectorDataSource.h"
#include "core/MapEnvelope.h"
#include "layers/Layer.h"

#include <memory>
#include <unordered_map>

namespace Nuti {
    class CullState;
    class ViewState;

    class Billboard;
    class GeometryCollection;
    class Label;
    class Line;
    class LineStyle;
    class Marker;
    class NMLModel;
    class Point;
    class Polygon3D;
    class Polygon;
    class Popup;
    
    class BillboardRenderer;
    class BillboardSorter;
    class GeometryCollectionRenderer;
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
        
        virtual bool isUpdateInProgress() const;
        
    protected:
        class DataSourceListener : public VectorDataSource::OnChangeListener {
        public:
            DataSourceListener(const std::shared_ptr<VectorLayer>& layer);
            
            virtual void onElementAdded(const std::shared_ptr<VectorElement>& element);
            virtual void onElementChanged(const std::shared_ptr<VectorElement>& element);
            virtual void onElementRemoved(const std::shared_ptr<VectorElement>& element);
            virtual void onElementsAdded(const std::vector<std::shared_ptr<VectorElement> >& elements);
            virtual void onElementsChanged();
            virtual void onElementsRemoved();
            
        private:
            std::weak_ptr<VectorLayer> _layer;
        };
        
        class FetchTask : public CancelableTask {
        public:
            FetchTask(const std::weak_ptr<VectorLayer>& layer);
            virtual void cancel();
            virtual void run();
            
        protected:
            std::weak_ptr<VectorLayer> _layer;
            
            bool _started;
            
            virtual bool loadElements(const std::shared_ptr<CullState>& cullState);
        };
        
        virtual void setComponents(const std::shared_ptr<CancelableThreadPool>& envelopeThreadPool,
                                   const std::shared_ptr<CancelableThreadPool>& tileThreadPool,
                                   const std::weak_ptr<Options>& options,
                                   const std::weak_ptr<MapRenderer>& mapRenderer,
								   const std::weak_ptr<TouchHandler>& touchHandler);
        
        virtual void loadData(const std::shared_ptr<CullState>& cullState);

        virtual void offsetLayerHorizontally(double offset) ;
        
        virtual void onSurfaceCreated(ShaderManager& shaderManager);
        virtual bool onDrawFrame(float deltaSeconds, BillboardSorter& billboardSorter, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
        virtual void onSurfaceDestroyed();
        
        virtual void calculateRayIntersectedElements(const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir,
                                                     const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;

        virtual void refreshElement(const std::shared_ptr<VectorElement>& element, bool remove);

        virtual void addRendererElement(const std::shared_ptr<VectorElement>& element);
        virtual bool refreshRendererElements();
        virtual bool syncRendererElement(const std::shared_ptr<VectorElement>& element, const ViewState& viewState, bool remove);
        
        virtual void registerDataSourceListener();
        virtual void unregisterDataSourceListener();

        virtual std::shared_ptr<CancelableTask> createFetchTask(const std::shared_ptr<CullState>& cullState);
    
        const DirectorPtr<VectorDataSource> _dataSource;
        std::shared_ptr<VectorDataSource::OnChangeListener> _dataSourceListener;
        
    private:
        std::shared_ptr<BillboardRenderer> _billboardRenderer;
        std::shared_ptr<GeometryCollectionRenderer> _geometryCollectionRenderer;
        std::shared_ptr<LineRenderer> _lineRenderer;
        std::shared_ptr<PointRenderer> _pointRenderer;
        std::shared_ptr<PolygonRenderer> _polygonRenderer;
        std::shared_ptr<Polygon3DRenderer> _polygon3DRenderer;
        std::shared_ptr<NMLModelRenderer> _nmlModelRenderer;
    
        std::shared_ptr<CancelableTask> _lastTask;
    };
    
}

#endif
