/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_PARSERUTILS_H_
#define _NUTI_MAPNIK_PARSERUTILS_H_

#include "Value.h"
#include "Expression.h"
#include "Transform.h"

#include <stdexcept>
#include <memory>
#include <string>
#include <vector>

namespace Nuti { namespace Mapnik {
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
	std::vector<std::shared_ptr<Transform>> parseTransformList(const std::string& str);
} }

#endif
