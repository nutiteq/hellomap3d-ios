/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_RASTERTILERENDERER_H_
#define _NUTI_RASTERTILERENDERER_H_

#include "drawdatas/RasterTileDrawData.h"
#include "utils/LRUTextureCache.h"

#include <mutex>

namespace Nuti {
    class MapPos;
    class Shader;
    class ShaderManager;
    class ViewState;
    
    class RasterTileRenderer {
    public:
        RasterTileRenderer(LRUTextureCache<long long>& visibleCache, LRUTextureCache<long long>& preloadingCache);
        virtual ~RasterTileRenderer();
    
        void offsetLayerHorizontally(double offset);
    
        void onSurfaceCreated(ShaderManager& shaderManager);
        bool onDrawFrame(float deltaSeconds, const ViewState& viewState);
        void onSurfaceDestroyed();
    
        void addDrawData(std::shared_ptr<RasterTileDrawData> drawData);
        void refreshDrawData();
    
    private:
        typedef std::vector<std::shared_ptr<RasterTileDrawData> > RasterTileDrawDataVector;
    
        void drawTiles(const MapPos& cameraPos, const RasterTileDrawDataVector& drawDatas, const ViewState& viewState);
        
        LRUTextureCache<long long>& _preloadingCache;
        LRUTextureCache<long long>& _visibleCache;
    
        RasterTileDrawDataVector _drawDatas;
        RasterTileDrawDataVector _tempDrawDatas;
    
        float _coordBuf[12];
        float _texCoordBuf[8];
    
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
