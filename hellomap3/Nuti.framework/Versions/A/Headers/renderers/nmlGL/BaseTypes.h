/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_NMLGL_BASETYPES_H_
#define _NUTI_NMLGL_BASETYPES_H_

#include "utils/GLES2.h"

#include <cglib/bbox.h>
#include <cglib/frustum3.h>
#include <cglib/mat.h>
#include <cglib/vec.h>

namespace Nuti { namespace nmlGL {
    
    struct Ray {
        cglib::vec3<double> origin;
        cglib::vec3<double> dir;
        
        Ray(const cglib::vec3<double>& origin, const cglib::vec3<double>& dir) : origin(origin), dir(dir) { }
    };
    
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
    
} }

#endif
