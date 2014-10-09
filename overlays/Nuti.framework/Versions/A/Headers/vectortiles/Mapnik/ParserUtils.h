#pragma once

#include "Value.h"
#include "Expression.h"

#include <memory>
#include <string>
#include <stdexcept>

namespace Nuti {
	namespace Mapnik {
		class ParserException : public std::runtime_error {
		public:
			ParserException(const std::string& msg, const std::string& source) : runtime_error(msg), _source(source) { }

			const std::string& string() const { return _source; }

		private:
			std::string _source;
		};

		unsigned int parseColor(const std::string& str);
		Value parseValue(const std::string& str);
		std::shared_ptr<Expression> parseExpression(const std::string& str);
		std::shared_ptr<Expression> parseStringExpression(const std::string& str);
	}
}
