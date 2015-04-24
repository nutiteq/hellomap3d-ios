/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_BASESHADER_H_
#define _NUTI_BASESHADER_H_

#include "utils/GLES2.h"

#include <unordered_map>
#include <string>

namespace Nuti {
    class ShaderSource;
    
    class BaseShader {
    public:
        BaseShader(const ShaderSource& source);
        virtual ~BaseShader();
        
        GLuint getProgId() const;
        GLuint getUniformLoc(const std::string& varName) const;
        GLuint getAttribLoc(const std::string& varName) const;
        
        void unload();
        
    protected:
        void registerVars(GLuint progId);
    
        std::string _progName;
    
        GLuint _progId;
        GLuint _vertShaderId;
        GLuint _fragShaderId;
    
        typedef std::unordered_map<std::string, GLuint> TVarMap;
        TVarMap _uniformMap;
        TVarMap _attribMap;
    };
    
}

#endif
