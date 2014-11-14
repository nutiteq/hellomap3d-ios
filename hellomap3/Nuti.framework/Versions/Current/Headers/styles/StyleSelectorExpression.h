#ifndef _NUTI_STYLESELECTOREXPRESSION_H_
#define _NUTI_STYLESELECTOREXPRESSION_H_

#include <memory>

namespace Nuti {
	class StyleSelectorContext;

	/**
	 * Style selector filter expression.
	 */
	class StyleSelectorExpression {
	public:
		virtual ~StyleSelectorExpression() = default;

		/**
		 * Evaluates filter expression given context.
		 * @param context The context to use for evaluation
		 * @return True or false, depending on the context.
		 */
		virtual bool evaluate(const StyleSelectorContext& context) const = 0;
	};
}

#endif
