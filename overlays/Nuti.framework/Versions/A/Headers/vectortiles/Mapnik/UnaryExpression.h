#pragma once

#include "Expression.h"

#include <memory>

namespace Nuti {
	namespace Mapnik {
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
	}
}
