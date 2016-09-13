/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_RASTERTILELAYER_H_
#define _NUTI_RASTERTILELAYER_H_

#include "TileLayer.h"
#include "components/CancelableTask.h"
#include "components/DirectorPtr.h"
#include "components/Task.h"
#include "core/MapTile.h"
#include "datasources/TileDataSource.h"
#include "renderers/RasterTileRenderer.h"
#include "utils/LRUCache.h"
#include "utils/LRUTextureCache.h"

#include <atomic>
#include <memory>
#include <unordered_set>

namespace Nuti {
    class TileLoadListener;
    
    /**
     * A tile layer where each tile is a bitmap. Should be used together with corresponding data source.
     */
    class RasterTileLayer: public TileLayer {
    public:
        /**
         * Constructs a RasterTileLayer object from a data source.
         * @param dataSource The data source from which this layer loads data.
         */
        RasterTileLayer(const std::shared_ptr<TileDataSource>& dataSource);
        virtual ~RasterTileLayer();
        
        /**
         * Returns the opacity of the layer.
         * @return The opacity of the layer. Default is 1 (fully opaque).
         */
        float getOpacity() const;
        /**
         * Sets the opacity attribute of the layer.
         * @param opacity The relative opacity. Use 0 for fully transparent layer, 1 for fully opaque layer. Default is 1.
         */
        void setOpacity(float opacity);
    
        /**
         * Returns the current frame number.
         * @return The current frame number.
         */
        int getFrameNr() const;
        /**
         * Sets the frame number, only used for animated tiles. Loading a new frame may take some time,
         * previous frame is shown during loading.
         * @param frameNr The frame number to display.
         */
        void setFrameNr(int frameNr);
    
        /**
         * Returns the state of the synchronized refresh flag.
         * @return The state of the synchronized refresh flag.
         */
        bool isSynchronizedRefresh() const;
        /**
         * Sets the state of the synchronized refresh flag. If disabled all tiles will appear on screen
         * one by one as they finish loading. If enabled the map will wait for all the visible tiles to finish loading
         * and then show them all on screen together. This is useful for animated tiles.
         * @param synchronizedRefresh The new state of the synchronized refresh flag.
         */
        void setSynchronizedRefresh(bool synchronizedRefresh);
    
        /**
         * Returns the tile load listener.
         * @return The tile load listener.
         */
        std::shared_ptr<TileLoadListener> getTileLoadListener() const;
        /**
         * Sets the tile load listener.
         * @param tileLoadListener The tile load listener.
         */
        void setTileLoadListener(const std::shared_ptr<TileLoadListener>& tileLoadListener);
    
        /**
         * Returns the tile texture cache capacity.
         * @return The tile texture cache capacity in bytes.
         */
        unsigned int getTextureCacheCapacity() const;
    
        /**
         * Sets the tile texture cache capacity. Texture cache is the primary storage for raster data,
         * all tiles contained within the texture cache are stored as uncompressed openGL textures and can immediately be
         * drawn to the screen. Setting the cache size too small may cause artifacts, such as disappearing tiles.
         * The more tiles are visible on the screen, the larger this cache should be. A single opaque 256x256 tile takes
         * up 192KB of memory, a transparent tile of the same size takes 256KB. The number of tiles on the screen depends
         * on the screen size and density, current rotation and tilt angle, tile draw size parameter and 
         * whether or not preloading is enabled.
         * The default is 10MB, which should be enough for most use cases with preloading enabled. If preloading is
         * disabled, the cache size should be reduced by the user to conserve memory.
         * @return The new tile bitmap cache capacity in bytes.
         */
        void setTextureCacheCapacity(unsigned int capacityInBytes);
    
        virtual void clearTileCaches(bool all);
    
    protected:
        class FetchTask : public TileLayer::FetchTaskBase {
        public:
            FetchTask(const std::shared_ptr<RasterTileLayer>& layer, const MapTile& tile, bool preloadingTile);
    
        protected:
            bool loadTile(const std::shared_ptr<TileLayer>& tileLayer);
			
		private:
			std::shared_ptr<Bitmap> extractSubTile(const std::shared_ptr<Bitmap>& bitmap, const MapTile& subTile, const MapTile& tile);
        };
    
        virtual bool tileExists(const MapTile& mapTile, bool preloadingCache);
        virtual bool tileIsValid(const MapTile& mapTile) const;
        virtual void fetchTile(const MapTileQuadTreeNode& mapTile, bool preloadingTile,bool invalidated);
    
        virtual void calculateDrawData(const MapTileQuadTreeNode& requestedTile, const MapTileQuadTreeNode& closestTile, bool preloadingTile);
        virtual void refreshDrawData(const std::shared_ptr<CullState>& cullState);
        
        virtual void tilesChanged(bool removeTiles);
        
        virtual int getMinZoom() const;
        virtual int getMaxZoom() const;
        
        virtual void offsetLayerHorizontally(double offset) ;
        
        virtual void onSurfaceCreated(ShaderManager& shaderManager);
        virtual bool onDrawFrame(float deltaSeconds, BillboardSorter& BillboardSorter, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
        virtual void onSurfaceDestroyed();
        
        virtual void calculateRayIntersectedElements(const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir,
                                                     const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;
    
        virtual void registerDataSourceListener();
        virtual void unregisterDataSourceListener();
    
    private:    
        static const int PRELOADING_PRIORITY_OFFSET = -2;
        static const int TILE_TEXTURES_PER_FRAME = 1;
        
        float _opacity;
    
        std::atomic<bool> _synchronizedRefresh;
    
        DirectorPtr<TileLoadListener> _tileLoadListener;
        mutable std::recursive_mutex _tileLoadListenerMutex;
    
        std::shared_ptr<RasterTileRenderer> _renderer;
        
        std::shared_ptr<LRUTextureCache<long long> > _visibleCache;
        std::shared_ptr<LRUTextureCache<long long> > _preloadingCache;
    };
    
}

#endif
