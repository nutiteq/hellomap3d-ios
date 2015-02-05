/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_STYLESELECTORRULE_H_
#define _NUTI_STYLESELECTORRULE_H_

#include <memory>

namespace Nuti {
    class Style;
    class StyleSelectorExpression;

    /**
     * Style selector rule. Rule is a combination of the optional filter and style.
     * If filter is present, then filter is evaluated to check if the style can be applied.
     */
    class StyleSelectorRule {
    public:
        /**
         * Constructs a new style selector rule, given filter expression and style.
         * @param expr The filter expression. Can be null pointer.
         * @param style The style of the rule.
         */
        StyleSelectorRule(const std::shared_ptr<StyleSelectorExpression>& expr, const std::shared_ptr<Style>& style);

        /**
         * Returns filter expression of this rule. Result can be null pointer.
         * @return The filter expression or null, if none is specified.
         */
        const std::shared_ptr<StyleSelectorExpression>& getExpression() const;
        /**
         * Returns the style associated with this rule.
         * @return The style.
         */
        const std::shared_ptr<Style>& getStyle() const;

    private:
        std::shared_ptr<StyleSelectorExpression> _expression;
        std::shared_ptr<Style> _style;
    };
}

#endif
