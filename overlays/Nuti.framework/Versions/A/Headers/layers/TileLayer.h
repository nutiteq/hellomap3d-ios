#ifndef TILELAYER_H_
#define TILELAYER_H_

#include "datasources/TileDataSource.h"
#include "layers/Layer.h"

#include <atomic>
#include <unordered_map>
#include <unordered_set>

namespace Nuti {

class CancelableTask;
class CullState;
class MapTile;
class MapTileQuadTreeNode;
    
/**
 * An abstract base class for all tile layers.
 */
class TileLayer : public Layer {
public:
    class FetchingTiles {
    public:
        FetchingTiles() : _fetchingTiles(), _mutex() {}
        
        void add(long long tileId) {
            std::lock_guard<std::mutex> lock(_mutex);
            _fetchingTiles.insert(tileId);
        }
        
        bool exists(long long tileId) {
            std::lock_guard<std::mutex> lock(_mutex);
            return _fetchingTiles.find(tileId) != _fetchingTiles.end();
        }
        
        void remove(long long tileId) {
            std::lock_guard<std::mutex> lock(_mutex);
            _fetchingTiles.erase(tileId);
        }
    private:
        std::unordered_set<long long> _fetchingTiles;
        mutable std::mutex _mutex;
    };
    
	virtual ~TileLayer();
    
    /**
     * Returns the data source assigned to this layer.
     * @return The tile data source assigned to this layer.
     */
    virtual std::shared_ptr<TileDataSource> getDataSource() = 0;

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
    * @param visible The new visibility state of the layer.
    */
	void setPreloading(bool preloading);

    /**
     * Gets the current zoom level bias for this layer.
     * @return The current zoom level bias for this layer.
     */
	float getZoomLevelBias() const;

    /**
     * Sets the zoom level bias for this layer. Higher zoom level bias forces SDK to use more detailed tiles for given view compared to lower zoom bias.
     * The default bias is 0.
     * @param The new bias value, both positive and negative fractional values are supported.
     */
	void setZoomLevelBias(float bias);

protected:
    struct DataSourceListener : public TileDataSource::OnChangeListener {
		DataSourceListener(TileLayer& tileLayer);
        
		virtual void onTilesChanged(TilesType tilesType, bool removeTiles);
        
		TileLayer& _layer;
	};
    
	TileLayer();

	void loadData(const std::shared_ptr<CullState>& cullState);

	virtual bool tileExists(const MapTile& tile, bool preloadingTile) = 0;
    virtual bool tileIsValid(const MapTile& tile, bool preloadingTile) const = 0;
	virtual void fetchTile(const MapTileQuadTreeNode& tile, bool preloadingTile, bool invalidated) = 0;

	virtual void calculateDrawData(const MapTileQuadTreeNode& requestedTile, const MapTileQuadTreeNode& closestTile, bool preloadingTile) = 0;
	virtual void refreshDrawData(const std::shared_ptr<CullState>& cullState) = 0;
    
    virtual void tilesChanged(TilesType tilesType, bool removeTiles) = 0;
    
    virtual int getMinZoom() const = 0;
    virtual int getMaxZoom() const = 0;
    
    std::atomic<bool> _calculatingTiles;
    std::atomic<bool> _refreshedTiles;

    DataSourceListener _dataSourceListener;
    
    FetchingTiles _fetchingTiles;
    
    int _frameNr;
    int _lastFrameNr;

    std::atomic<bool> _preloading;

    std::atomic<float> _zoomLevelBias;

	std::unordered_map<long long int, std::shared_ptr<CancelableTask> > _lastVisibleTasks;
	std::unordered_map<long long int, std::shared_ptr<CancelableTask> > _lastPreloadingTasks;

private:
    static bool DistanceComparator(const MapTileQuadTreeNode* tile1, const MapTileQuadTreeNode* tile2);
    
    void calculateVisibleTiles(const std::shared_ptr<CullState>& cullState);
    void calculateVisibleTilesRecursive(const std::shared_ptr<CullState>& cullState,
                                        MapTileQuadTreeNode& mapTile,
                                        const Frustum& preloadingFrustum,
                                        const MapPos& preloadingCameraPos);
    
	void findTiles(const std::vector<MapTileQuadTreeNode*>& tile, bool preloadingTiles);
	bool findParentTile(const MapTileQuadTreeNode& requestedTile, const MapTileQuadTreeNode* parentTile, int depth, bool preloadingTile);
	int findChildTiles(MapTileQuadTreeNode& requestedTile, int depth, bool preloadingTile);

	static const int MAX_PARENT_SEARCH_DEPTH = 6;
    static const int MAX_CHILD_SEARCH_DEPTH = 3;
    
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
