/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_SHADER_H_
#define _NUTI_SHADER_H_

#include "graphics/BaseShader.h"
#include "utils/GLES2.h"

namespace Nuti {
    class ShaderSource;

    class Shader : public BaseShader {
    public:
        Shader(const ShaderSource& source);
        virtual ~Shader();

    private:
        void load(const ShaderSource& source);

        GLuint loadProg(GLuint vertShaderId, GLuint fragShaderId) const;
        GLuint loadShader(const std::string& source, GLenum shaderType) const;
    };

}

#endif
