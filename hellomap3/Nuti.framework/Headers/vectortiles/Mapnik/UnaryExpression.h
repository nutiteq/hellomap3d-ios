/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_UNARYEXPRESSION_H_
#define _NUTI_MAPNIK_UNARYEXPRESSION_H_

#include "Expression.h"

#include <memory>

namespace Nuti { namespace Mapnik {
	class UnaryExpression : public Expression {
	public:
		struct Operator {
			virtual ~Operator() = default;

			virtual Value apply(const Value& val) const = 0;
		};
			
		UnaryExpression(const std::shared_ptr<Operator>& op, const std::shared_ptr<Expression>& expr) : _op(op), _expr(expr) { }

		const std::shared_ptr<Operator>& getOperator() const { return _op; }

		const std::shared_ptr<Expression>& getExpression() const { return _expr; }

		virtual Value evaluate(const ExpressionContext& context) const override {
			return _op->apply(_expr->evaluate(context));
		}

	private:
		const std::shared_ptr<Operator> _op;
		const std::shared_ptr<Expression> _expr;
	};
} }

#endif
