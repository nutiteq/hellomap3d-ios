#ifndef NMLMODELLODTREELAYER_H_
#define NMLMODELLODTREELAYER_H_

#include "layers/Layer.h"
#include "components/CancelableTask.h"
#include "datasources/NMLModelLODTreeDataSource.h"
#include "renderers/NMLModelLODTreeRenderer.h"
#include "graphics/ViewState.h"

#include <queue>
#include <memory>

namespace stdext {
    template <typename K, typename V>
    class lru_cache;
}

namespace Nuti {

class CullState;

/**
 * An advanced layer for 3D models that supports automatic Level of Detail (LOD) calculation based on view.
 * Should be used together with corresponding data source.
 */
class NMLModelLODTreeLayer : public Layer {
public:
    /**
     * Constructs a NMLModelLODTreeLayer object from a data source.
     * @param dataSource The data source from which this layer loads data.
     */
	NMLModelLODTreeLayer(std::shared_ptr<NMLModelLODTreeDataSource> dataSource);
	virtual ~NMLModelLODTreeLayer();

	/**
	 * Set memory usage constraints for the layer. The specified limit is not exact, 
	 * but should be relatively close to the actual memory usage of the layer.
	 * If specific view requires more data than specified limit, then lower LOD levels
	 * of the models are used. The default is 40MB.
	 * @param size The memory limit in bytes.
	 */
	void setMaxMemorySize(size_t size);

	/**
	 * Set relative model LOD resolution. Higher values than 1 result in higher details 
     * (but slower performance and higher memory usage), while lower values give better 
     * performance but lower quality. The default is 1.
	 * @param factor The relative LOD resolution factor.
	 */
	void setLODResolutionFactor(float factor);

protected:
    virtual void offsetLayerHorizontally(double offset) ;
    
	virtual void onSurfaceCreated(ShaderManager& shaderManager);
	virtual bool onDrawFrame(float deltaSeconds, BillboardSorter& BillboardSorter, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache,
                             const ViewState& viewState);
	virtual void onSurfaceDestroyed();
    
	virtual void calculateRayIntersectedElements(const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir,
                                                 const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;
    
	virtual void registerDataSourceListener();
	virtual void unregisterDataSourceListener();

	virtual void loadData(const std::shared_ptr<CullState>& cullState);

private:
	typedef NMLModelLODTreeDataSource::MapTileList MapTileList;
	typedef std::map<long long, std::shared_ptr<NMLModelLODTree> > ModelLODTreeMap;
	typedef stdext::lru_cache<long long, std::shared_ptr<NMLModelLODTree> > ModelLODTreeCache;
	typedef std::map<long long, NMLPackage::GLMeshPtr> MeshMap;
	typedef stdext::lru_cache<long long, NMLPackage::GLMeshPtr> MeshCache;
	typedef std::map<long long, NMLPackage::GLTexturePtr> TextureMap;
	typedef stdext::lru_cache<long long, NMLPackage::GLTexturePtr> TextureCache;
	typedef std::map<long long, std::shared_ptr<NMLModelLODTreeDrawData> > NodeDrawDataMap;

	class FetchTask : public CancelableTask {
	public:
		FetchTask(const std::weak_ptr<NMLModelLODTreeLayer>& layer, const ViewState& viewState);
		virtual void run();

	private:
        std::weak_ptr<NMLModelLODTreeLayer> _layer;
		ViewState _viewState;
	};

	void updateDrawLists(const ViewState& viewState, const ModelLODTreeMap& modelLODTreeMap, MeshMap& meshMap, TextureMap& textureMap, NodeDrawDataMap& nodeDrawDataMap);
	void loadModelLODTrees(const MapTileList& mapTileList, ModelLODTreeMap& modelLODTreeMap);
	void loadMeshes(const NMLModelLODTree* modelLODTree, int nodeId, NMLPackage::GLModelPtr glModel, MeshMap& meshMap);
	void loadTextures(const NMLModelLODTree* modelLODTree, int nodeId, NMLPackage::GLModelPtr glModel, TextureMap& textureMap);

	size_t _maxMemorySize;
	float _LODResolutionFactor;

	MapTileList _mapTileList;
	ViewState _mapTileListViewState;
	ModelLODTreeMap _modelLODTreeMap;
    std::unique_ptr<ModelLODTreeCache> _modelLODTreeCache;
	MeshMap _meshMap;
	std::unique_ptr<MeshCache> _meshCache;
	TextureMap _textureMap;
	std::unique_ptr<TextureCache> _textureCache;
	NodeDrawDataMap _nodeDrawDataMap;

	std::shared_ptr<NMLModelLODTreeDataSource> _dataSource;
	std::shared_ptr<NMLModelLODTreeRenderer> _renderer;
	
	std::shared_ptr<CancelableTask> _lastTask;
};

}

#endif
