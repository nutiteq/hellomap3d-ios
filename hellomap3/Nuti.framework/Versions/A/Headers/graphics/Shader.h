/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_SHADER_H_
#define _NUTI_SHADER_H_

#include "utils/GLES2.h"

#include <string>
#include <unordered_map>

namespace Nuti {
    class ShaderSource;

    class Shader {
    public:
        Shader(const ShaderSource& source);
        virtual ~Shader();

        GLuint getProgId() const;
        GLuint getUniformLoc(const std::string& varName) const;
        GLuint getAttribLoc(const std::string& varName) const;
        
        void unload();

    private:
        void load(const ShaderSource& source);
        void registerVars(GLuint progId);
        
        GLuint loadProg(GLuint vertShaderId, GLuint fragShaderId) const;
        GLuint loadShader(const std::string& source, GLenum shaderType) const;

        std::string _progName;
        
        GLuint _progId;
        GLuint _vertShaderId;
        GLuint _fragShaderId;
        
        std::unordered_map<std::string, GLuint> _uniformMap;
        std::unordered_map<std::string, GLuint> _attribMap;
    };

}

#endif
