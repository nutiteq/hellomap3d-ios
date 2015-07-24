/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_TILELAYER_H_
#define _NUTI_TILELAYER_H_

#include "components/CancelableTask.h"
#include "components/DirectorPtr.h"
#include "datasources/TileDataSource.h"
#include "layers/Layer.h"
#include "utils/LRUCache.h"

#include <atomic>
#include <unordered_map>

namespace Nuti {
    class CancelableTask;
    class CullState;
    class MapTile;
    class MapTileQuadTreeNode;
    
    namespace TileSubstitutionPolicy {
        /**
         * The policy to use when looking for tiles that are not available.
         */
        enum TileSubstitutionPolicy {
            /**
             * Consider all cached/loaded tiles.
             */
            TILE_SUBSTITUTION_POLICY_ALL,
            /**
             * Consider only tiles that are currently visible.
             * This is recommended for low-latency data sources, like offline sources.
             */
            TILE_SUBSTITUTION_POLICY_VISIBLE,
            /**
             * Never substitute tiles.
             */
            TILE_SUBSTITUTION_POLICY_NONE
        };
    }
        
    /**
     * An abstract base class for all tile layers.
     */
    class TileLayer : public Layer {
    public:
        virtual ~TileLayer();
        
        /**
         * Returns the data source assigned to this layer.
         * @return The tile data source assigned to this layer.
         */
        std::shared_ptr<TileDataSource> getDataSource() const;
    
        /**
         * Returns the state of the preloading flag of this layer.
         * @return True if preloading is enabled.
         */
        bool isPreloading() const;
    
        /**
         * Sets the state of preloading for this layer. Preloading allows the downloading of tiles that are not
         * currently visible on screen, but are adjacent to ones that are. This means that the user can pan the map without
         * immediately noticing any missing tiles.
         *
         * Enabling this option might introduce a small performance hit on slower devices. It should also be noted that this
         * will considerably increase network traffic if used with online maps. The default is false.
         * @param preloading The new preloading state of the layer.
         */
        void setPreloading(bool preloading);
        
        /**
         * Returns the current tile substitution policy.
         * @return The current substitution policy. Default is TILE_SUBSTITUTION_POLICY_ALL.
         */
        TileSubstitutionPolicy::TileSubstitutionPolicy getTileSubstitutionPolicy() const;
        /**
         * Sets the current tile substitution policy.
         * @param policy The new substitution policy. Default is TILE_SUBSTITUTION_POLICY_ALL.
         */
        void setTileSubstitutionPolicy(TileSubstitutionPolicy::TileSubstitutionPolicy policy);
        
        /**
         * Gets the current zoom level bias for this layer.
         * @return The current zoom level bias for this layer.
         */
        float getZoomLevelBias() const;
        /**
         * Sets the zoom level bias for this layer. Higher zoom level bias forces SDK to use more detailed tiles for given view compared to lower zoom bias.
         * The default bias is 0.
         * @param bias The new bias value, both positive and negative fractional values are supported.
         */
        void setZoomLevelBias(float bias);
        
        /**
         * Calculate tile corresponding to given geographical coordinates and zoom level.
         * Note: zoom level bias is NOT applied, only discrete zoom level is used.
         * @param mapPos Coordinates of the point in data source projection coordinate system.
         * @param zoom Zoom level to use for the tile.
         * @return corresponding map tile.
         */
        MapTile calculateMapTile(const MapPos& mapPos, int zoom) const;
        /**
         * Calculate origin map coordinates of given map tile.
         * @param mapTile The map tile to use.
         * @return corresponding coordinates of the tile origin in data source projection coordinate system.
         */
        MapPos calculateMapTileOrigin(const MapTile& mapTile) const;
        
        /**
         * Clear layer tile caches. This will release memory allocated to tiles.
         * @param all True if all tiles should be released, otherwise only preloading (invisible) tiles are released.
         */
        virtual void clearTileCaches(bool all) = 0;

        virtual bool isUpdateInProgress() const;
        
    protected:
        class DataSourceListener : public TileDataSource::OnChangeListener {
        public:
            DataSourceListener(const std::shared_ptr<TileLayer>& layer);
            
            virtual void onTilesChanged(bool removeTiles);
            
        private:
            std::weak_ptr<TileLayer> _layer;
        };
        
        class FetchTaskBase : public CancelableTask {
        public:
            FetchTaskBase(const std::shared_ptr<TileLayer>& layer, const MapTileQuadTreeNode& tile, bool preloadingTile);
			
			bool isPreloading() const;
			void invalidate();
            virtual void cancel();
            virtual void run();
			
        protected:
            virtual bool loadTile(const std::shared_ptr<TileLayer>& layer) = 0;
            
            std::weak_ptr<TileLayer> _layer;
            MapTile _tile; // original tile
            std::vector<MapTile> _dataSourceTiles; // tiles in valid datasource range, ordered to top
            bool _preloadingTile;
            
            bool _started;
			bool _invalidated;
        };
        
		class FetchingTileTasks {
		public:
			FetchingTileTasks() : _fetchingTiles(), _mutex() {}
			
			void add(long long tileId, const std::shared_ptr<FetchTaskBase>& task) {
				std::lock_guard<std::mutex> lock(_mutex);
				_fetchingTiles[tileId] = task;
			}
			
			bool exists(long long tileId) {
				std::lock_guard<std::mutex> lock(_mutex);
				return _fetchingTiles.find(tileId) != _fetchingTiles.end();
			}
			
			void remove(long long tileId) {
				std::lock_guard<std::mutex> lock(_mutex);
				_fetchingTiles.erase(tileId);
			}
			
			std::vector<std::shared_ptr<FetchTaskBase> > getTasks() const {
				std::lock_guard<std::mutex> lock(_mutex);
				std::vector<std::shared_ptr<FetchTaskBase> > tasks;
				for (const auto& pair : _fetchingTiles) {
					tasks.push_back(pair.second);
				}
				return tasks;
			}
			
			int getPreloadingCount() const {
				std::lock_guard<std::mutex> lock(_mutex);
				int count = 0;
				for (const auto& pair : _fetchingTiles) {
					if (pair.second->isPreloading()) {
						count++;
					}
				}
				return count;
			}
			
			int getVisibleCount() const {
				std::lock_guard<std::mutex> lock(_mutex);
				int count = 0;
				for (const auto& pair : _fetchingTiles) {
					if (!pair.second->isPreloading()) {
						count++;
					}
				}
				return count;
			}

		private:
			std::unordered_map<long long, std::shared_ptr<FetchTaskBase> > _fetchingTiles;
			mutable std::mutex _mutex;
		};
		
        TileLayer(const std::shared_ptr<TileDataSource>& dataSource);
		
        virtual void loadData(const std::shared_ptr<CullState>& cullState);
		
        virtual bool tileExists(const MapTile& tile, bool preloadingCache) = 0;
        virtual bool tileIsValid(const MapTile& tile) const = 0;
        virtual void fetchTile(const MapTileQuadTreeNode& tile, bool preloadingTile, bool invalidated) = 0;
    
        virtual void calculateDrawData(const MapTileQuadTreeNode& requestedTile, const MapTileQuadTreeNode& closestTile, bool preloadingTile) = 0;
        virtual void refreshDrawData(const std::shared_ptr<CullState>& cullState) = 0;
        
        virtual void tilesChanged(bool removeTiles) = 0;
        
        virtual int getMinZoom() const = 0;
        virtual int getMaxZoom() const = 0;
        
        std::atomic<bool> _calculatingTiles;
        std::atomic<bool> _refreshedTiles;
		
        const DirectorPtr<TileDataSource> _dataSource;
        std::shared_ptr<DataSourceListener> _dataSourceListener;
        
        FetchingTileTasks _fetchingTiles;
        
        int _frameNr;
        int _lastFrameNr;
    
        bool _preloading;
        
        TileSubstitutionPolicy::TileSubstitutionPolicy _substitutionPolicy;
    
        float _zoomLevelBias;
    
    private:
        static bool DistanceComparator(const MapTileQuadTreeNode* tile1, const MapTileQuadTreeNode* tile2);
        
        void calculateVisibleTiles(const std::shared_ptr<CullState>& cullState);
        void calculateVisibleTilesRecursive(const std::shared_ptr<CullState>& cullState, MapTileQuadTreeNode& mapTile);
        
        void findTiles(const std::vector<MapTileQuadTreeNode*>& tile, bool preloadingTiles);
        bool findParentTile(const MapTileQuadTreeNode& requestedTile, const MapTileQuadTreeNode* parentTile, int depth, bool preloadingCache, bool preloadingTile);
        int findChildTiles(MapTileQuadTreeNode& requestedTile, int depth, bool preloadingCache, bool preloadingTile);
    
        static const int MAX_PARENT_SEARCH_DEPTH = 6;
        static const int MAX_CHILD_SEARCH_DEPTH = 3;
        
        static const float PRELOADING_TILE_SCALE;
        static const float SUBDIVISION_THRESHOLD;
        static const float SQRT_2;
        
        std::unique_ptr<MapTileQuadTreeNode> _centerRoot;
        std::unique_ptr<MapTileQuadTreeNode> _leftRoot;
        std::unique_ptr<MapTileQuadTreeNode> _rightRoot;
        
        std::vector<MapTileQuadTreeNode*> _visibleTiles;
        std::vector<MapTileQuadTreeNode*> _preloadingTiles;
    };
    
}

#endif
