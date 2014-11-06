#ifndef _NUTI_STYLESELECTOR_H_
#define _NUTI_STYLESELECTOR_H_

#include <memory>
#include <vector>

namespace Nuti {
	class Style;
	class StyleSelectorRule;
	class StyleSelectorContext;

	/**
	 * A collection of style rules.
	 */
	class StyleSelector {
	public:
		/**
		 * Constructs a new style selector from a list of rules.
		 * @param rules The list of rules to use.
		 */
		StyleSelector(const std::vector<std::shared_ptr<StyleSelectorRule> >& rules);

		/**
		 * Get matching style for given context.
		 * @param context The context to use for matching.
		 * @return First matching style or null pointer if no matching style was found.
		 */
		const std::shared_ptr<Style>& getStyle(const StyleSelectorContext& context) const;

	protected:
		std::vector<std::shared_ptr<StyleSelectorRule> > _rules;
	};
}

#endif
