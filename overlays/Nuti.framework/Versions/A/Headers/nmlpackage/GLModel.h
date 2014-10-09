#ifndef GLMODEL_H_
#define GLMODEL_H_

#include "core/MapBounds.h"
#include "nmlpackage/BaseTypes.h"
#include "nmlpackage/GLMesh.h"
#include "nmlpackage/GLMeshInstance.h"
#include "nmlpackage/GLTexture.h"

#include <list>
#include <map>
#include <memory>
#include <string>

namespace NMLPackage {

class Model;

class GLModel {
public:
	GLModel(const NMLPackage::Model& model);
		
	void create(const GLContextPtr& gl);
	void dispose(const GLContextPtr& gl);

	void replaceMesh(const std::string& id, const GLMeshPtr& glMesh);
	void replaceTexture(const std::string& id, const GLTexturePtr& glTexture);

	void draw(const GLContextPtr& gl);

	void calculateRayIntersections(const cglib::vec3<double>& origin, const cglib::vec3<double>& dir, std::vector<RayIntersection>& intersections) const;

	int getDrawCallCount() const;
	int getTotalGeometrySize() const;

private:
	cglib::bounding_box<float, 3> _bounds;
	std::map<std::string, GLMeshPtr> _meshMap;
	std::map<std::string, GLTexturePtr> _textureMap;
	std::list<GLMeshInstancePtr> _meshInstanceList;
};

typedef std::shared_ptr<GLModel> GLModelPtr;

}

#endif
