/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_GLSHADERMANAGER_H_
#define _NUTI_VT_GLSHADERMANAGER_H_

#include "GLExtensions.h"

#include <memory>
#include <string>
#include <map>
#include <set>

namespace Nuti { namespace VT {
	class GLShaderManager {
	public:
		using ShaderContext = std::shared_ptr<const std::set<std::string>>;
		
		GLuint createProgram(const std::string& programName, const ShaderContext& context);
		void resetPrograms();
		void deletePrograms();

	private:
		static std::string createShader(const std::string& name, const std::map<std::string, const std::string*>& shaderMap, const std::set<std::string>& defs);
		
		std::map<std::pair<std::string, ShaderContext>, GLuint> _programMap;
	};
} }

#endif
