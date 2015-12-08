/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_BACKGROUNDRENDERER_H_
#define _NUTI_BACKGROUNDRENDERER_H_

#include "utils/GLES2.h"

#include <memory>

namespace Nuti {
    class Bitmap;
    class Options;
    class ShaderManager;
    class Shader;
    class Texture;
    class ViewState;
    
    class BackgroundRenderer {
    public:
        BackgroundRenderer(const Options& options);
        virtual ~BackgroundRenderer();
    
        void onSurfaceCreated(ShaderManager& shaderManager);
        void onDrawFrame(const ViewState& viewState);
        void onSurfaceDestroyed();
    
    protected:
        void drawBackground(const ViewState& viewState);
        void drawSky(const ViewState& viewState);
    
        const static float BACKGROUND_COORDS[];
        const static float BACKGROUND_TEX_COORDS[];
        const static int BACKGROUND_VERTEX_COUNT = 4;
    
        const static float SKY_COORDS[];
        const static float SKY_TEX_COORDS[];
        const static int SKY_VERTEX_COUNT = 16;
        const static float SKY_SCALE_MULTIPLIER;
    
        std::shared_ptr<Bitmap> _backgroundBitmap;
        std::unique_ptr<Texture> _backgroundTex;
        float _backgroundCoords[BACKGROUND_VERTEX_COUNT * 3];
        float _backgroundTexCoords[BACKGROUND_VERTEX_COUNT * 2];
    
        std::shared_ptr<Bitmap> _skyBitmap;
        std::unique_ptr<Texture> _skyTex;
        float _skyCoords[SKY_VERTEX_COUNT * 3];
    
        const Shader* _shader;
        GLuint _u_tex;
        GLuint _u_mvpMat;
        GLuint _a_coord;
        GLuint _a_texCoord;
    
        const Options& _options;
    };
    
}

#endif
