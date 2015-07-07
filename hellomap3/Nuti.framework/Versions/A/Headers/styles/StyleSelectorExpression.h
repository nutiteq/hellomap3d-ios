/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

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
		virtual ~StyleSelectorExpression() { }

        /**
         * Evaluates filter expression given context.
         * @param context The context to use for evaluation
         * @return True or false, depending on the context.
         */
        virtual bool evaluate(const StyleSelectorContext& context) const = 0;
    };
}

#endif
