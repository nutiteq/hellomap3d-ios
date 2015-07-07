/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_POINTRENDERER_H_
#define _NUTI_POINTRENDERER_H_

#include "utils/LRUTextureCache.h"

#include <deque>
#include <memory>
#include <mutex>

namespace Nuti {
    class Bitmap;
    class Point;
    class PointDrawData;
    class Shader;
    class ShaderManager;
    class VectorElement;
    class VectorElementClickInfo;
    class VectorLayer;
    class ViewState;
    
    class PointRenderer {
    public:
        PointRenderer();
        virtual ~PointRenderer();
    
        virtual void offsetLayerHorizontally(double offset);
    
        virtual void onSurfaceCreated(ShaderManager& shaderManager);
        virtual void onDrawFrame(float deltaSeconds, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
        virtual void onSurfaceDestroyed();
    
        void addElement(const std::shared_ptr<Point>& element);
        void refreshElements();
        void updateElement(const std::shared_ptr<Point>& element);
        void removeElement(const std::shared_ptr<Point>& element);
    
        virtual void calculateRayIntersectedElements(const std::shared_ptr<VectorLayer>& layer, const MapPos& rayOrig, const MapVec& rayDir, const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;

    protected:
        friend class GeometryCollectionRenderer;

    private:
        static void BuildAndDrawBuffers(GLuint a_color,
                                        GLuint a_coord,
                                        GLuint a_texCoord,
                                        std::vector<unsigned char>& colorBuf,
                                        std::vector<float>& coordBuf,
                                        std::vector<unsigned short>& indexBuf,
                                        std::vector<float>& texCoordBuf,
                                        std::vector<std::shared_ptr<PointDrawData> >& drawDataBuffer,
                                        const MapBounds& texCoordBounds,
                                        LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache,
                                        const ViewState& viewState);
        
        static bool FindElementRayIntersection(const std::shared_ptr<VectorElement>& element,
                                               const std::shared_ptr<PointDrawData>& drawData,
                                               const std::shared_ptr<VectorLayer>& layer,
                                               const MapPos& rayOrig, const MapVec& rayDir,
                                               const ViewState& viewState,
                                               std::vector<VectorElementClickInfo>& results);

        void bind(const ViewState& viewState);
        void unbind();
        
        bool isEmptyBatch() const;
        void addToBatch(const std::shared_ptr<PointDrawData>& drawData, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
        void drawBatch(LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
        void drawBuffers(int indexCount) const;
    
        std::vector<std::shared_ptr<Point> > _elements;
        std::vector<std::shared_ptr<Point> > _tempElements;
        
        std::vector<std::shared_ptr<PointDrawData> > _drawDataBuffer;
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
