#pragma once

#include "Value.h"
#include "Expression.h"

#include <string>
#include <memory>
#include <stdexcept>

namespace Nuti {
	namespace Mapnik {
		class GeneratorException : public std::runtime_error {
		public:
			GeneratorException(const std::string& msg) : runtime_error(msg) { }
		};

		std::string generateColorString(unsigned int color);
		std::string generateValueString(const Value& val);
		std::string generateExpressionString(const std::shared_ptr<Expression>& expr);
	}
}
