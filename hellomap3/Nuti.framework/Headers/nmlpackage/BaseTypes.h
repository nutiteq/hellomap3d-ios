#ifndef BASETYPES_H_
#define BASETYPES_H_

#include "utils/GLES2.h"

#include <memory>

#include <cglib/bbox.h>
#include <cglib/frustum3.h>
#include <cglib/mat.h>
#include <cglib/vec.h>

namespace NMLPackage {
	
struct RayIntersection {
	unsigned int vertexId;
	cglib::vec3<double> pos;
	cglib::vec3<double> normal;

	RayIntersection(unsigned int vertexId, const cglib::vec3<double>& pos, const cglib::vec3<double>& normal) : vertexId(vertexId), pos(pos), normal(normal) { }
};

struct GLContext {
	virtual ~GLContext() { }
	virtual GLuint getUniformLocation(const char *name) const = 0;
	virtual GLuint getAttribLocation(const char *name) const = 0;
	virtual void setLocalModelviewMatrix(const float matrix[]) = 0;
};

typedef std::shared_ptr<GLContext> GLContextPtr;

}

#endif
