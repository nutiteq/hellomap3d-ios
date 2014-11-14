/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_FILTER_H_
#define _NUTI_MAPNIK_FILTER_H_

#include "Expression.h"

#include <memory>

namespace Nuti { namespace Mapnik {
	class Filter {
	public:
		enum class Type {
			FILTER,
			ELSEFILTER,
			ALSOFILTER
		};

		Filter(Type type, const std::shared_ptr<Expression>& expr) : _type(type), _expr(expr) { }

		Type getType() const { return _type; }
		const std::shared_ptr<Expression>& getExpression() const { return _expr; }

	private:
		const Type _type;
		const std::shared_ptr<Expression> _expr;
	};
} }

#endif
