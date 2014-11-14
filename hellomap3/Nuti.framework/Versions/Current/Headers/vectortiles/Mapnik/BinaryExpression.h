/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_BINARYEXPRESSION_H_
#define _NUTI_MAPNIK_BINARYEXPRESSION_H_

#include "Expression.h"

#include <memory>
#include <stdexcept>

namespace Nuti { namespace Mapnik {
	class BinaryExpression : public Expression {
	public:
		struct Operator {
			virtual ~Operator() = default;

			virtual Value apply(const Value& val1, const Value& val2) const = 0;
		};

		BinaryExpression(const std::shared_ptr<Operator>& op, const std::shared_ptr<Expression>& expr1, const std::shared_ptr<Expression>& expr2) : _op(op), _expr1(expr1), _expr2(expr2) { }

		const std::shared_ptr<Operator>& getOperator() const { return _op; }

		const std::shared_ptr<Expression>& getExpression(int n) const {
			switch (n) {
			case 0:
				return _expr1;
			case 1:
				return _expr2;
			default:
				throw std::invalid_argument("Expression index out of range");
			}
		}

		virtual Value evaluate(const ExpressionContext& context) const override {
			return _op->apply(_expr1->evaluate(context), _expr2->evaluate(context));
		}

	protected:
		const std::shared_ptr<Operator> _op;
		const std::shared_ptr<Expression> _expr1;
		const std::shared_ptr<Expression> _expr2;
	};

	class BinaryOrExpression : public BinaryExpression {
	public:
		BinaryOrExpression(const std::shared_ptr<Operator>& op, const std::shared_ptr<Expression>& expr1, const std::shared_ptr<Expression>& expr2) : BinaryExpression(op, expr1, expr2) { }

		virtual Value evaluate(const ExpressionContext& context) const override {
			Value val1 = _expr1->evaluate(context);
			if (val1.getType() != Value::Type::BOOL_VALUE) {
				return Value();
			}
			if (val1.getBool()) {
				return Value(true);
			}
			Value val2 = _expr2->evaluate(context);
			if (val2.getType() != Value::Type::BOOL_VALUE) {
				return Value();
			}
			return val2;
		}
	};

	class BinaryAndExpression : public BinaryExpression {
	public:
		BinaryAndExpression(const std::shared_ptr<Operator>& op, const std::shared_ptr<Expression>& expr1, const std::shared_ptr<Expression>& expr2) : BinaryExpression(op, expr1, expr2) { }

		virtual Value evaluate(const ExpressionContext& context) const override {
			Value val1 = _expr1->evaluate(context);
			if (val1.getType() != Value::Type::BOOL_VALUE) {
				return Value();
			}
			if (!val1.getBool()) {
				return Value(false);
			}
			Value val2 = _expr2->evaluate(context);
			if (val2.getType() != Value::Type::BOOL_VALUE) {
				return Value();
			}
			return val2;
		}
	};
} }

#endif
