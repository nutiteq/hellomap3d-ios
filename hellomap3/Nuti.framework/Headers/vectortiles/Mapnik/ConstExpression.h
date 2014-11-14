/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_CONSTEXPRESSION_H_
#define _NUTI_MAPNIK_CONSTEXPRESSION_H_

#include "Expression.h"

namespace Nuti { namespace Mapnik {
	class ConstExpression : public Expression {
	public:
		explicit ConstExpression(const Value& constant) : _constant(constant) { }

		const Value& getConstant() const { return _constant; }

		virtual Value evaluate(const ExpressionContext& context) const override {
			return _constant;
		}

	private:
		const Value _constant;
	};
} }

#endif
