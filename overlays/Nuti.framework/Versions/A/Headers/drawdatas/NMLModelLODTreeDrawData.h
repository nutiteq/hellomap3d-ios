#ifndef NMLMODELLODTREEDRAWDATA_H_
#define NMLMODELLODTREEDRAWDATA_H_

#include "VectorElementDrawData.h"
#include "vectorelements/NMLModelLODTree.h"
#include "nmlpackage/GLModel.h"

#include <memory>

namespace Nuti {

class NMLModelLODTreeDrawData : public VectorElementDrawData {
public:
	NMLModelLODTreeDrawData(const std::shared_ptr<NMLModelLODTree>& modelLODTree, long long nodeId, const std::vector<long long>& parentIds, const NMLPackage::GLModelPtr& glModel);

	std::shared_ptr<NMLModelLODTree> getModelLODTree() const;
	long long getNodeId() const;
	const std::vector<long long>& getParentIds() const;
	const cglib::mat4x4<double>& getLocalMat() const;
	const NMLPackage::GLModelPtr& getGLModel() const;
	const std::shared_ptr<NMLModelLODTree::ProxyMap> getProxyMap() const;

private:
	std::shared_ptr<NMLModelLODTree> _modelLODTree;
	long long _nodeId;
	std::vector<long long> _parentIds;
	cglib::mat4x4<double> _localMat;
	NMLPackage::GLModelPtr _glModel;
	std::shared_ptr<NMLModelLODTree::ProxyMap> _proxyMap;
};

}

#endif
