#pragma once

#include "Value.h"

namespace Nuti {
	namespace Mapnik {
		class ExpressionContext;

		class Expression {
		public:
			virtual ~Expression() = default;
			
			virtual Value evaluate(const ExpressionContext& context) const = 0;
		};
	}
}
