/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NMLMODELLODTREELAYER_H_
#define _NUTI_NMLMODELLODTREELAYER_H_

#include "layers/Layer.h"
#include "components/CancelableTask.h"
#include "components/CancelableThreadPool.h"
#include "datasources/NMLModelLODTreeDataSource.h"
#include "renderers/NMLModelLODTreeRenderer.h"
#include "graphics/ViewState.h"
#include "utils/LRUCache.h"

#include <memory>

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
        NMLModelLODTreeLayer(const std::shared_ptr<NMLModelLODTreeDataSource>& dataSource);
        virtual ~NMLModelLODTreeLayer();
    
        /**
         * Returns the data source of this layer.
         * @return The data source that was bound to this vector layer on construction.
         */
        std::shared_ptr<NMLModelLODTreeDataSource> getDataSource() const;

        /**
         * Returns memory usage constraints for the layer.
         * @return The memory usage constraints for the layer.
         */
        unsigned int getMaxMemorySize() const;
        /**
         * Set memory usage constraints for the layer. The specified limit is not exact, 
         * but should be relatively close to the actual memory usage of the layer.
         * If specific view requires more data than specified limit, then lower LOD levels
         * of the models are used. The default is 40MB.
         * @param size The memory limit in bytes.
         */
        void setMaxMemorySize(unsigned int size);

        /**
         * Returns relative model LOD resolution.
         * @return The relative model LOD resolution.
         */
        float getLODResolutionFactor() const;
        /**
         * Set relative model LOD resolution. Higher values than 1 result in higher details 
         * (but slower performance and higher memory usage), while lower values give better 
         * performance but lower quality. The default is 1.
         * @param factor The relative LOD resolution factor.
         */
        void setLODResolutionFactor(float factor);
    
        virtual bool isUpdateInProgress() const;

    protected:
        virtual void offsetLayerHorizontally(double offset) ;
    
        virtual void onSurfaceCreated(ShaderManager& shaderManager);
        virtual bool onDrawFrame(float deltaSeconds, BillboardSorter& BillboardSorter, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
        virtual void onSurfaceDestroyed();
    
        virtual void calculateRayIntersectedElements(const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir, const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;
    
        virtual void registerDataSourceListener();
        virtual void unregisterDataSourceListener();
    
        virtual void loadData(const std::shared_ptr<CullState>& cullState);
    
    private:
        typedef std::vector<NMLModelLODTreeDataSource::MapTile> MapTileList;
        typedef std::map<long long, std::shared_ptr<NMLModelLODTree> > ModelLODTreeMap;
        typedef LRUCache<long long, std::shared_ptr<NMLModelLODTree> > ModelLODTreeCache;
        typedef std::map<long long, std::shared_ptr<nmlGL::Mesh> > MeshMap;
        typedef LRUCache<long long, std::shared_ptr<nmlGL::Mesh> > MeshCache;
        typedef std::map<long long, std::shared_ptr<nmlGL::Texture> > TextureMap;
        typedef LRUCache<long long, std::shared_ptr<nmlGL::Texture> > TextureCache;
        typedef std::map<long long, std::shared_ptr<NMLModelLODTreeDrawData> > NodeDrawDataMap;
    
        class FetchingTasks {
        public:
            FetchingTasks() : _fetchingTasks(), _mutex() {}
            
            int getTaskCount() const {
                std::lock_guard<std::mutex> lock(_mutex);
                return static_cast<int>(_fetchingTasks.size());
            }
            
            void add(long long taskId) {
                std::lock_guard<std::mutex> lock(_mutex);
                _fetchingTasks.insert(taskId);
            }
            
            bool exists(long long taskId) {
                std::lock_guard<std::mutex> lock(_mutex);
                return _fetchingTasks.find(taskId) != _fetchingTasks.end();
            }
            
            void remove(long long taskId) {
                std::lock_guard<std::mutex> lock(_mutex);
                _fetchingTasks.erase(taskId);
            }
        private:
            std::unordered_set<long long> _fetchingTasks;
            mutable std::mutex _mutex;
        };
    
        class MapTilesFetchTask : public CancelableTask {
        public:
            MapTilesFetchTask(const std::shared_ptr<NMLModelLODTreeLayer>& layer, const std::shared_ptr<CullState>& cullState);
            virtual void run();
    
        private:
            std::weak_ptr<NMLModelLODTreeLayer> _layer;
            std::shared_ptr<CullState> _cullState;
        };
    
        class ModelLODTreeFetchTask : public CancelableTask {
        public:
            ModelLODTreeFetchTask(const std::shared_ptr<NMLModelLODTreeLayer>& layer, const NMLModelLODTreeDataSource::MapTile& mapTile);
            virtual void cancel();
            virtual void run();
    
        private:
            std::weak_ptr<NMLModelLODTreeLayer> _layer;
            NMLModelLODTreeDataSource::MapTile _mapTile;
        };
    
        class MeshFetchTask : public CancelableTask {
        public:
            MeshFetchTask(const std::shared_ptr<NMLModelLODTreeLayer>& layer, const NMLModelLODTree::MeshBinding& binding);
            virtual void cancel();
            virtual void run();
    
        private:
            std::weak_ptr<NMLModelLODTreeLayer> _layer;
            NMLModelLODTree::MeshBinding _binding;
        };
    
        class TextureFetchTask : public CancelableTask {
        public:
            TextureFetchTask(const std::shared_ptr<NMLModelLODTreeLayer>& layer, const NMLModelLODTree::TextureBinding& binding);
            virtual void cancel();
            virtual void run();
    
        private:
            std::weak_ptr<NMLModelLODTreeLayer> _layer;
            NMLModelLODTree::TextureBinding _binding;
        };
    
        bool isDataAvailable(const NMLModelLODTree* modelLODTree, int nodeId);
        bool loadModelLODTrees(const MapTileList& mapTileList, bool checkOnly);
        bool loadMeshes(const NMLModelLODTree* modelLODTree, int nodeId, bool checkOnly);
        bool loadTextures(const NMLModelLODTree* modelLODTree, int nodeId, bool checkOnly);
        void updateModelLODTrees(const MapTileList& mapTileList, ModelLODTreeMap& modelLODTreeMap);
        void updateMeshes(const NMLModelLODTree* modelLODTree, int nodeId, std::shared_ptr<nmlGL::Model> glModel, MeshMap& meshMap);
        void updateTextures(const NMLModelLODTree* modelLODTree, int nodeId, std::shared_ptr<nmlGL::Model> glModel, TextureMap& textureMap);
        void updateDrawLists(const ViewState& viewState, MeshMap& meshMap, TextureMap& textureMap, NodeDrawDataMap& nodeDrawDataMap);
    
        static const int MODELLODTREE_LOADING_PRIORITY_OFFSET = 1;
        static const int MESH_LOADING_PRIORITY_OFFSET = 0;
        static const int TEXTURE_LOADING_PRIORITY_OFFSET = 0;
    
        unsigned int _maxMemorySize;
        float _LODResolutionFactor;
    
        MapTileList _mapTileList;
        ViewState _mapTileListViewState;
        ModelLODTreeMap _modelLODTreeMap;
        std::shared_ptr<ModelLODTreeCache> _modelLODTreeCache;
        MeshMap _meshMap;
        std::shared_ptr<MeshCache> _meshCache;
        TextureMap _textureMap;
        std::shared_ptr<TextureCache> _textureCache;
        NodeDrawDataMap _nodeDrawDataMap;
    
        FetchingTasks _fetchingModelLODTrees;
        FetchingTasks _fetchingMeshes;
        FetchingTasks _fetchingTextures;
        
        std::shared_ptr<CancelableThreadPool> _fetchThreadPool;
    
        std::shared_ptr<NMLModelLODTreeDataSource> _dataSource;
        std::shared_ptr<NMLModelLODTreeRenderer> _renderer;
    };
    
}

#endif
