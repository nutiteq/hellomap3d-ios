#pragma once

#include "Expression.h"

#include <memory>

namespace Nuti {
	namespace Mapnik {
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
	}
}
