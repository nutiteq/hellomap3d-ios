/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VECTORTILELAYER_H_
#define _NUTI_VECTORTILELAYER_H_

#include "TileLayer.h"
#include "components/CancelableTask.h"
#include "components/Task.h"
#include "core/MapTile.h"
#include "utils/LRUCache.h"
#include "vectortiles/VectorTileDecoder.h"

#include <memory>
#include <map>
#include <unordered_set>

namespace Nuti {
    class VectorTileRenderer;
        
    namespace VT {
        struct TileId;
        class Tile;
    }
    
    /**
     * A tile layer where each tile is a bitmap. Should be used together with corresponding data source.
     */
    class VectorTileLayer : public TileLayer {
    public:
        /**
         * Constructs a VectorTileLayer object from a data source and tile decoder.
         * @param dataSource The data source from which this layer loads data.
         * @param decoder The tile decoder that decoder loaded tiles and applies styles.
         */
        VectorTileLayer(const std::shared_ptr<TileDataSource>& dataSource, const std::shared_ptr<VectorTileDecoder>& decoder);
        virtual ~VectorTileLayer();
    
        /**
         * Returns the tile decoder assigned to this layer.
         * @return The tile decoder assigned to this layer.
         */
        virtual std::shared_ptr<VectorTileDecoder> getTileDecoder();
        
        /**
         * Returns the tile cache capacity.
         * @return The tile cache capacity in bytes.
         */
        unsigned int getTileCacheCapacity() const;
    
        /**
         * Sets the vector tile cache capacity. Tile cache is the primary storage for vector data,
         * all tiles contained within the cache are stored as uncompressed vertex buffers and can immediately be
         * drawn to the screen. Setting the cache size too small may cause artifacts, such as disappearing tiles.
         * The more tiles are visible on the screen, the larger this cache should be. 
         * The default is 10MB, which should be enough for most use cases with preloading enabled. If preloading is
         * disabled, the cache size should be reduced by the user to conserve memory.
         * @return The new tile bitmap cache capacity in bytes.
         */
        void setTileCacheCapacity(unsigned int capacityInBytes);
    
        virtual void clearTileCaches(bool all);
        
    protected:
        virtual int getCullDelay() const;
    
        virtual bool tileExists(const MapTile& mapTile, bool preloadingTile);
        virtual bool tileIsValid(const MapTile& mapTile, bool preloadingTile) const;
        virtual void fetchTile(const MapTileQuadTreeNode& mapTile, bool preloadingTile, bool invalidated);
    
        virtual void calculateDrawData(const MapTileQuadTreeNode& requestedTile, const MapTileQuadTreeNode& closestTile, bool preloadingTile);
        virtual void refreshDrawData(const std::shared_ptr<CullState>& cullState);
    
        virtual void tilesChanged(bool removeTiles);
        
        virtual int getMinZoom() const;
        virtual int getMaxZoom() const;
        
        virtual void offsetLayerHorizontally(double offset) ;
        
        virtual void onSurfaceCreated(ShaderManager& shaderManager);
        virtual bool onDrawFrame(float deltaSeconds, BillboardSorter& BillboardSorter, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
		virtual bool onDrawFrame3D(float deltaSeconds, BillboardSorter& BillboardSorter, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
        virtual void onSurfaceDestroyed();
        
        virtual void calculateRayIntersectedElements(const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir,
                                                     const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;
    
        virtual void registerDataSourceListener();
        virtual void unregisterDataSourceListener();
    
    private:    
        class TileDecoderListener : public VectorTileDecoder::OnChangeListener {
        public:
            TileDecoderListener(const std::shared_ptr<VectorTileLayer>& layer);
            
            virtual void onDecoderChanged();
    
        private:
            std::weak_ptr<VectorTileLayer> _layer;
        };
    
        class FetchTask : public TileLayer::FetchTaskBase {
        public:
            FetchTask(const std::shared_ptr<VectorTileLayer>& layer, const MapTileQuadTreeNode& tile, bool preloadingTile);
            
        protected:
            bool loadTile(const std::shared_ptr<TileLayer>& tileLayer);
        };
        
        class LabelCullTask : public CancelableTask {
        public:
            LabelCullTask(const std::shared_ptr<VectorTileLayer>& layer, const std::shared_ptr<VectorTileRenderer>& renderer, const ViewState& viewState);
            
            virtual void cancel();
            virtual void run();
    
        private:
            std::weak_ptr<VectorTileLayer> _layer;
            std::weak_ptr<VectorTileRenderer> _renderer;
            ViewState _viewState;
        };
    
        static const int CULL_DELAY_TIME = 200;
        static const int PRELOADING_PRIORITY_OFFSET = -2;
    
        std::shared_ptr<VectorTileDecoder> _tileDecoder;
        std::shared_ptr<VectorTileRenderer> _renderer;
        std::shared_ptr<CancelableThreadPool> _labelCullThreadPool;
    
        std::shared_ptr<TileDecoderListener> _tileDecoderListener;
    
        std::map<VT::TileId, std::shared_ptr<VT::Tile> > _visibleTileMap, _prevVisibleTileMap;
        
        LRUCache<long long, std::shared_ptr<VT::Tile> > _visibleCache;
        LRUCache<long long, std::shared_ptr<VT::Tile> > _preloadingCache;
    };
    
}

#endif
