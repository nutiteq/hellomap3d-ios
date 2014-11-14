#ifndef GLMESH_H_
#define GLMESH_H_

#include "nmlpackage/BaseTypes.h"
#include "nmlpackage/GLSubmesh.h"

#include <cassert>
#include <memory>
#include <vector>

namespace NMLPackage {

class Mesh;
class MeshOp;

class GLMesh {
public:
	GLMesh(const NMLPackage::Mesh& mesh);
	GLMesh(const GLMesh& glMesh, const NMLPackage::MeshOp& meshOp);

	void create(const GLContextPtr& gl);
	void dispose(const GLContextPtr& gl);

	const std::vector<GLSubmeshPtr>& getSubmeshList() const;

	int getTotalGeometrySize() const;

private:
	std::vector<GLSubmeshPtr> _submeshList;
};

typedef std::shared_ptr<GLMesh> GLMeshPtr;

}

#endif
