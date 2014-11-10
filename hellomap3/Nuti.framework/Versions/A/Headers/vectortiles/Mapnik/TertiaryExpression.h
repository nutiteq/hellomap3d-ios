#pragma once

#include "Expression.h"

#include <memory>
#include <stdexcept>

namespace Nuti {
	namespace Mapnik {
		class TertiaryExpression : public Expression {
		public:
			struct Operator {
				virtual ~Operator() = default;

				virtual Value apply(const Value& val1, const Value& val2, const Value& val3) const = 0;
			};

			TertiaryExpression(const std::shared_ptr<Operator>& op, const std::shared_ptr<Expression>& expr1, const std::shared_ptr<Expression>& expr2, const std::shared_ptr<Expression>& expr3) : _op(op), _expr1(expr1), _expr2(expr2), _expr3(expr3) { }

			const std::shared_ptr<Operator>& getOperator() const { return _op; }

			const std::shared_ptr<Expression>& getExpression(int n) const {
				switch (n) {
				case 0:
					return _expr1;
				case 1:
					return _expr2;
				case 2:
					return _expr3;
				default:
					throw std::invalid_argument("Expression index out of range");
				}
			}

			virtual Value evaluate(const ExpressionContext& context) const override {
				return _op->apply(_expr1->evaluate(context), _expr2->evaluate(context), _expr3->evaluate(context));
			}

		private:
			const std::shared_ptr<Operator> _op;
			const std::shared_ptr<Expression> _expr1;
			const std::shared_ptr<Expression> _expr2;
			const std::shared_ptr<Expression> _expr3;
		};
	}
}
