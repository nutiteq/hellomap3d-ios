/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NMLMODELLODTREEDRAWDATA_H_
#define _NUTI_NMLMODELLODTREEDRAWDATA_H_

#include "VectorElementDrawData.h"
#include "vectorelements/NMLModelLODTree.h"

#include <memory>

namespace Nuti {
    namespace nmlGL {
        class Model;
    }
    
    class NMLModelLODTreeDrawData : public VectorElementDrawData {
    public:
        NMLModelLODTreeDrawData(const std::shared_ptr<NMLModelLODTree>& modelLODTree, long long nodeId, const std::vector<long long>& parentIds, const std::shared_ptr<nmlGL::Model>& glModel);
    
        std::shared_ptr<NMLModelLODTree> getModelLODTree() const;
        long long getNodeId() const;
        const std::vector<long long>& getParentIds() const;
        const cglib::mat4x4<double>& getLocalMat() const;
        const std::shared_ptr<nmlGL::Model>& getGLModel() const;
        const std::shared_ptr<NMLModelLODTree::ProxyMap> getProxyMap() const;
    
    private:
        std::shared_ptr<NMLModelLODTree> _modelLODTree;
        long long _nodeId;
        std::vector<long long> _parentIds;
        cglib::mat4x4<double> _localMat;
        std::shared_ptr<nmlGL::Model> _glModel;
        std::shared_ptr<NMLModelLODTree::ProxyMap> _proxyMap;
    };
    
}

#endif
