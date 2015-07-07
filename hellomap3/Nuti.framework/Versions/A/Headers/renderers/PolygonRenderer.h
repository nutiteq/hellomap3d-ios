/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_POLYGONRENDERER_H_
#define _NUTI_POLYGONRENDERER_H_

#include "utils/LRUTextureCache.h"

#include <deque>
#include <memory>
#include <mutex>

namespace Nuti {
    class Bitmap;
    class LineDrawData;
    class Polygon;
    class PolygonDrawData;
    class Shader;
    class ShaderManager;
    class VectorElement;
    class VectorElementClickInfo;
    class VectorLayer;
    class ViewState;
    
    class PolygonRenderer {
    public:
        PolygonRenderer();
        virtual ~PolygonRenderer();
    
        void offsetLayerHorizontally(double offset);
    
        void onSurfaceCreated(ShaderManager& shaderManager);
        void onDrawFrame(float deltaSeconds, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
        void onSurfaceDestroyed();
    
        void addElement(const std::shared_ptr<Polygon>& element);
        void refreshElements();
        void updateElement(const std::shared_ptr<Polygon>& element);
        void removeElement(const std::shared_ptr<Polygon>& element);
        
        void calculateRayIntersectedElements(const std::shared_ptr<VectorLayer>& layer, const MapPos& rayOrig, const MapVec& rayDir, const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;
    
    protected:
        friend class GeometryCollectionRenderer;

    private:
        static void BuildAndDrawBuffers(GLuint a_color,
                                        GLuint a_coord,
                                        std::vector<unsigned char>& colorBuf,
                                        std::vector<float>& coordBuf,
                                        std::vector<unsigned short>& indexBuf,
                                        std::vector<std::shared_ptr<PolygonDrawData> >& drawDataBuffer,
                                        LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache,
                                        const ViewState& viewState);
        
        static bool FindElementRayIntersection(const std::shared_ptr<VectorElement>& element,
                                               const std::shared_ptr<PolygonDrawData>& drawData,
                                               const std::shared_ptr<VectorLayer>& layer,
                                               const MapPos& rayOrig, const MapVec& rayDir,
                                               const ViewState& viewState,
                                               std::vector<VectorElementClickInfo>& results);

        void bind(const ViewState& viewState);
        void unbind();
        
        bool isEmptyBatch() const;
        void addToBatch(const std::shared_ptr<PolygonDrawData>& drawData, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
        void drawBatch(LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
    
        std::vector<std::shared_ptr<Polygon> > _elements;
        std::vector<std::shared_ptr<Polygon> > _tempElements;
        
        std::vector<std::shared_ptr<PolygonDrawData> > _drawDataBuffer;
        std::vector<const LineDrawData*> _lineDrawDataBuffer;
        const Bitmap* _prevBitmap;
    
        std::vector<unsigned char> _colorBuf;
        std::vector<float> _coordBuf;
        std::vector<unsigned short> _indexBuf;
        std::vector<float> _texCoordBuf;
    
        const Shader* _shader;
        GLuint _a_color;
        GLuint _a_coord;
        GLuint _a_texCoord;
        GLuint _u_mvpMat;
        GLuint _u_tex;
    
        mutable std::mutex _mutex;
    };
    
}

#endif
