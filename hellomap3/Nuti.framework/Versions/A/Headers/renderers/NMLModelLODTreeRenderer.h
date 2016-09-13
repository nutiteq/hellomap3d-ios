/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NMLMODELLODTREERENDERER_H_
#define _NUTI_NMLMODELLODTREERENDERER_H_

#include "renderers/NMLModelRendererBase.h"
#include "renderers/drawdatas/NMLModelLODTreeDrawData.h"
#include "renderers/nmlGL/Model.h"
#include "vectorelements/NMLModelLODTree.h"

#include <list>
#include <vector>

namespace Nuti {
    class NMLModelLODTreeDataSource;
    class NMLModelLODTreeLayer;
    
    class NMLModelLODTreeRenderer : public NMLModelRendererBase {
    public:
        NMLModelLODTreeRenderer();
        virtual ~NMLModelLODTreeRenderer();
    
        void addDrawData(const std::shared_ptr<NMLModelLODTreeDrawData>& drawData);
        void refreshDrawData();
        
        virtual void offsetLayerHorizontally(double offset);
    
        virtual void calculateRayIntersectedElements(const std::shared_ptr<NMLModelLODTreeLayer>& layer, const MapPos& rayOrig, const MapVec& rayDir, const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;
    
    protected:
        struct ModelNodeDrawRecord {
            NMLModelLODTreeDrawData drawData;
            ModelNodeDrawRecord* parent;
            std::vector<ModelNodeDrawRecord *> children;
            bool used;
            bool created;
    
            ModelNodeDrawRecord(const NMLModelLODTreeDrawData& drawData) : drawData(drawData), parent(0), children(), used(false), created(false) { }
        };
    
        std::vector<std::shared_ptr<NMLModelLODTreeDrawData> > _tempDrawDatas;
        std::map<long long, std::shared_ptr<ModelNodeDrawRecord> > _drawRecordMap;
    
        virtual bool drawModels(const ViewState& viewState);
    };
    
}

#endif
