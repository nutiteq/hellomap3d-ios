/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_GEOMETRYCOLLECTIONRENDERER_H_
#define _NUTI_GEOMETRYCOLLECTIONRENDERER_H_

#include "renderers/LineRenderer.h"
#include "renderers/PointRenderer.h"
#include "renderers/PolygonRenderer.h"

#include <deque>
#include <memory>
#include <mutex>

namespace Nuti {
    class Bitmap;
    class GeometryCollection;
    class GeometryCollectionDrawData;
    class Projection;
    class Shader;
    class ShaderManager;
    class VectorElementClickInfo;
    class VectorLayer;
    class ViewState;

    class GeometryCollectionRenderer {
    public:
        GeometryCollectionRenderer();
        virtual ~GeometryCollectionRenderer();

        virtual void offsetLayerHorizontally(double offset);

        virtual void onSurfaceCreated(ShaderManager& shaderManager);
        virtual void onDrawFrame(float deltaSeconds, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
        virtual void onSurfaceDestroyed();

        void addElement(const std::shared_ptr<GeometryCollection>& element);
        void refreshElements();
        void updateElement(const std::shared_ptr<GeometryCollection>& element);
        void removeElement(const std::shared_ptr<GeometryCollection>& element);

        virtual void calculateRayIntersectedElements(const std::shared_ptr<VectorLayer>& layer, const MapPos& rayOrig, const MapVec& rayDir,
            const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;

    private:
        std::vector<std::shared_ptr<GeometryCollection> > _elements;
        std::vector<std::shared_ptr<GeometryCollection> > _tempElements;

        PointRenderer _pointRenderer;
        LineRenderer _lineRenderer;
        PolygonRenderer _polygonRenderer;

        mutable std::mutex _mutex;
    };

}

#endif
