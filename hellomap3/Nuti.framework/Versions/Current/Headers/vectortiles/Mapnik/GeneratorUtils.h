/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_GENERATORUTILS_H_
#define _NUTI_MAPNIK_GENERATORUTILS_H_

#include "Value.h"
#include "Expression.h"

#include <string>
#include <memory>
#include <stdexcept>

namespace Nuti { namespace Mapnik {
	class GeneratorException : public std::runtime_error {
	public:
		GeneratorException(const std::string& msg) : runtime_error(msg) { }
	};

	std::string generateColorString(unsigned int color);
	std::string generateValueString(const Value& val);
	std::string generateExpressionString(const std::shared_ptr<Expression>& expr);
} }

#endif
