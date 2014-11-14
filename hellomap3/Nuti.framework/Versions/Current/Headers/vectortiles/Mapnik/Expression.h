/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_EXPRESSION_H_
#define _NUTI_MAPNIK_EXPRESSION_H_

#include "Value.h"

namespace Nuti { namespace Mapnik {
	class ExpressionContext;

	class Expression {
	public:
		virtual ~Expression() = default;
			
		virtual Value evaluate(const ExpressionContext& context) const = 0;
	};
} }

#endif
