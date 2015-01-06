/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NMLMODELLODTREERENDERER_H_
#define _NUTI_NMLMODELLODTREERENDERER_H_

#include "renderers/NMLModelRendererBase.h"
#include "vectorelements/NMLModelLODTree.h"
#include "drawdatas/NMLModelLODTreeDrawData.h"
#include "drawdatas/nmlGL/Model.h"

#include <list>
#include <vector>

namespace Nuti {
    class NMLModelLODTreeDataSource;
    
    class NMLModelLODTreeRenderer : public NMLModelRendererBase {
    public:
        NMLModelLODTreeRenderer();
        virtual ~NMLModelLODTreeRenderer();
    
        void addDrawData(const std::shared_ptr<NMLModelLODTreeDrawData>& drawData);
        void refreshDrawData();
    
        virtual void calculateRayIntersectedElements(const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir,
                        const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;
    
    protected:
        typedef std::vector<std::shared_ptr<NMLModelLODTreeDrawData> > DrawDataVector;
    
        struct ModelNodeDrawRecord {
            NMLModelLODTreeDrawData drawData;
            ModelNodeDrawRecord* parent;
            std::vector<ModelNodeDrawRecord *> children;
            bool used;
            bool created;
    
            ModelNodeDrawRecord(const NMLModelLODTreeDrawData& drawData) : drawData(drawData), parent(0), children(), used(false), created(false) { }
        };
    
        typedef std::map<long long, std::shared_ptr<ModelNodeDrawRecord> > ModelNodeDrawRecordMap;
    
        DrawDataVector _tempDrawDatas;
        ModelNodeDrawRecordMap _drawRecordMap;
    
        virtual bool drawModels(const ViewState& viewState);
    };
    
}

#endif
