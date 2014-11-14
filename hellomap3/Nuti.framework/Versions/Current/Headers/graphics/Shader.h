#ifndef SHADER_H_
#define SHADER_H_

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
