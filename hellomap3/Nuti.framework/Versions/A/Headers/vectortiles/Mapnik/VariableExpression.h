#pragma once

#include "Expression.h"
#include "ExpressionContext.h"

#include <string>

namespace Nuti {
	namespace Mapnik {
		class VariableExpression : public Expression {
		public:
			explicit VariableExpression(const std::string& variable) : _variable(variable) { }

			const std::string& getVariable() const { return _variable; }

			virtual Value evaluate(const ExpressionContext& context) const override {
				return context.getVariable(_variable);
			}

		private:
			const std::string _variable;
		};
	}
}
