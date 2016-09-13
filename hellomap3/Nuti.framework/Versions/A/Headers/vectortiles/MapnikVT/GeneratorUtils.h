/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_GENERATORUTILS_H_
#define _NUTI_MAPNIKVT_GENERATORUTILS_H_

#include "Value.h"
#include "Expression.h"
#include "Transform.h"
#include "VT/Color.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace Nuti { namespace MapnikVT {
	class GeneratorException : public std::runtime_error {
	public:
		explicit GeneratorException(const std::string& msg) : runtime_error(msg) { }
	};

	std::string generateColorString(VT::Color color);
	std::string generateValueString(const Value& val);
	std::string generateExpressionString(const std::shared_ptr<Expression>& expr);
    std::string generateStringExpressionString(const std::shared_ptr<Expression>& expr);
    std::string generateTransformListString(const std::vector<std::shared_ptr<Transform>>& transforms);
} }

#endif
