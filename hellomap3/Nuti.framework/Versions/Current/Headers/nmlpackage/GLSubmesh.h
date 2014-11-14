#ifndef GLSUBMESH_H_
#define GLSUBMESH_H_

#include "nmlpackage/BaseTypes.h"

#include <memory>
#include <vector>

namespace NMLPackage {

class Submesh;
class SubmeshOpList;
class GLMesh;

class GLSubmesh {
public:
	GLSubmesh(const NMLPackage::Submesh& submesh);
	GLSubmesh(const GLMesh& glMesh, const NMLPackage::SubmeshOpList& submeshOpList);

	void create(const GLContextPtr& gl);
	void dispose(const GLContextPtr& gl);

	void draw(const GLContextPtr& gl);

	void calculateRayIntersections(const cglib::vec3<double>& origin, const cglib::vec3<double>& dir, std::vector<RayIntersection>& intersections) const;

	const std::string& getMaterialId() const;

	int getDrawCallCount() const;
	int getTotalGeometrySize() const;

private:
	void uploadSubmesh(const GLContextPtr& gl);

	static GLint convertType(int type);
	static void convertToFloatBuffer(const std::string& str, std::vector<float>& buf);
	static void convertToByteBuffer(const std::string& str, std::vector<unsigned char>& buf);

	int _refCount;
	GLint _glType;
	std::vector<int> _vertexCounts;
	std::string _materialId;

	std::vector<float> _positionBuffer;
	std::vector<float> _normalBuffer;
	std::vector<float> _uvBuffer;
	std::vector<unsigned char> _colorBuffer;
	std::vector<unsigned int> _vertexIdBuffer;

	GLuint _glPositionVBOId;
	GLuint _glNormalVBOId;
	GLuint _glUVVBOId;
	GLuint _glColorVBOId;
	std::weak_ptr<GLContext> _glContext;
};

typedef std::shared_ptr<GLSubmesh> GLSubmeshPtr;

}

#endif
