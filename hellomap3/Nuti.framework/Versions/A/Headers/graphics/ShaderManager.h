#ifndef SHADERMANAGER_H_
#define SHADERMANAGER_H_

#include "graphics/Shader.h"

#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace Nuti {
    
class ShaderSource;
    
class ShaderManager {
public:
	ShaderManager();
	virtual ~ShaderManager();

	const Shader& createShader(const ShaderSource& source);

	void removeAll(bool destroyShaders);

private:
	typedef std::unordered_map<const ShaderSource*, Shader> ShaderMap;

	ShaderMap _shaderMap;
};

}

#endif
