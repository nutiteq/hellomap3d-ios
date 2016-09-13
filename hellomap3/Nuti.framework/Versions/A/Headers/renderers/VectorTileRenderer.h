/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VECTORTILERENDERER_H_
#define _NUTI_VECTORTILERENDERER_H_

#include "graphics/Color.h"
#include "graphics/ViewState.h"
#include "vectortiles/VT/TileId.h"
#include "vectortiles/VT/Tile.h"

#include <memory>
#include <mutex>
#include <map>

namespace Nuti {
    class MapPos;
    class Projection;
    class Shader;
    class ShaderManager;
    class MapRenderer;
    class ViewState;
	namespace VT {
		class GLTileRenderer;
	}
    
	class VectorTileRenderer : public std::enable_shared_from_this<VectorTileRenderer> {
    public:
        VectorTileRenderer(const std::weak_ptr<MapRenderer>& mapRenderer, bool useFBO, bool useDepth, bool useStencil);
        virtual ~VectorTileRenderer();
    
        void setLabelOrder(int labelOrder);

        void offsetLayerHorizontally(double offset);
    
        void onSurfaceCreated(ShaderManager& shaderManager);
        bool onDrawFrame(float deltaSeconds, const ViewState& viewState);
        bool onDrawFrame3D(float deltaSeconds, const ViewState& viewState);
        void onSurfaceDestroyed();
    
        void setBackgroundColor(const Color& color);
        void setBackgroundPattern(const std::shared_ptr<const VT::BitmapPattern>& pattern);
        bool cullLabels(const ViewState& viewState);
        bool refreshTiles(const std::map<VT::TileId, std::shared_ptr<const VT::Tile> >& tiles);
    
    private:
        std::weak_ptr<MapRenderer> _mapRenderer;
        std::shared_ptr<VT::GLTileRenderer> _glRenderer;
        std::shared_ptr<std::mutex> _glRendererMutex;
        bool _useFBO;
        bool _useDepth;
        bool _useStencil;
        int _labelOrder;
        double _horizontalLayerOffset;
        std::map<VT::TileId, std::shared_ptr<const VT::Tile> > _tiles;

        mutable std::mutex _mutex;
    };
    
}

#endif
