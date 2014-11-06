#pragma once

#include "Expression.h"

namespace Nuti {
	namespace Mapnik {
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
	}
}
