/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_STYLE_H_
#define _NUTI_MAPNIKVT_STYLE_H_

#include <memory>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace Nuti { namespace MapnikVT {
    class Expression;
    class Rule;
	
    class Style {
	public:
		enum class FilterMode {
			ALL,
			FIRST
		};

        explicit Style(std::string name, float opacity, std::string compOp, FilterMode filterMode, std::vector<std::shared_ptr<Rule>> rules);

		const std::string& getName() const { return _name; }
		float getOpacity() const { return _opacity; }
        const std::string& getCompOp() const { return _compOp; }
		FilterMode getFilterMode() const { return _filterMode; }
		const std::vector<std::shared_ptr<Rule>>& getRules() const { return _rules; }
			
        const std::vector<std::shared_ptr<Rule>>& getZoomRules(int zoom) const;

        const std::unordered_set<std::shared_ptr<Expression>>& getReferencedFields(int zoom) const;

	private:
		const std::string _name;
		const float _opacity;
        const std::string _compOp;
		const FilterMode _filterMode;
		const std::vector<std::shared_ptr<Rule>> _rules;
		std::unordered_map<int, std::vector<std::shared_ptr<Rule>>> _zoomRuleMap;
        std::unordered_map<int, std::unordered_set<std::shared_ptr<Expression>>> _zoomFieldExprsMap;
    };
} }

#endif
