#ifndef GLMESHINSTANCE_H_
#define GLMESHINSTANCE_H_

#include "nmlpackage/BaseTypes.h"
#include "nmlpackage/GLMaterial.h"
#include "nmlpackage/GLMesh.h"

#include <list>
#include <map>
#include <memory>
#include <string>

namespace NMLPackage {

class MeshInstance;

class GLMeshInstance {
public:
	GLMeshInstance(const NMLPackage::MeshInstance& meshInstance, const std::map<std::string, GLMeshPtr>& meshMap, const std::map<std::string, GLTexturePtr>& textureMap);

	void replaceMesh(const std::string& meshId, const GLMeshPtr& glMesh);
	void replaceTexture(const std::string& textureId, const GLTexturePtr& glTexture);

	void draw(const GLContextPtr& gl);

	void calculateRayIntersections(const cglib::vec3<double>& origin, const cglib::vec3<double>& dir, std::vector<RayIntersection>& intersections) const;

	int getDrawCallCount() const;

private:
	std::string _meshId;
	GLMeshPtr _mesh;
	std::map<std::string, GLMaterialPtr> _materialMap;
	bool _transformEnabled;
	cglib::mat4x4<float> _transformMatrix;
};

typedef std::shared_ptr<GLMeshInstance> GLMeshInstancePtr;

}

#endif
