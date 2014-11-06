#pragma once

#include "Rule.h"
#include "ScaleUtils.h"

#include <memory>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

namespace Nuti {
	namespace Mapnik {
		class Style {
		public:
			enum class FilterMode {
				ALL,
				FIRST
			};

			Style(const std::string& name, float opacity, FilterMode filterMode, const std::vector<std::shared_ptr<Rule>>& rules) : _name(name), _opacity(opacity), _filterMode(filterMode), _rules(rules), _zoomRuleMap() {
				for (auto it = rules.begin(); it != rules.end(); it++) {
					const std::shared_ptr<Rule>& rule = *it;
					float minZoom = std::max(static_cast<float>(0), scaleDenominator2Zoom(rule->getMaxScaleDenominator()));
					float maxZoom = std::min(static_cast<float>(MAX_SUPPORTED_ZOOM_LEVEL), scaleDenominator2Zoom(rule->getMinScaleDenominator()));
					for (int zoom = static_cast<int>(std::floor(minZoom)); zoom <= static_cast<int>(std::ceil(maxZoom)); zoom++) {
						_zoomRuleMap[zoom].push_back(rule);
					}
				}
			}

			const std::string& getName() const { return _name; }
			float getOpacity() const { return _opacity; }
			FilterMode getFilterMode() const { return _filterMode; }
			const std::vector<std::shared_ptr<Rule>>& getRules() const { return _rules; }
			
			const std::vector<std::shared_ptr<Rule>>& getZoomRules(int zoom) const {
				auto it = _zoomRuleMap.find(zoom);
				if (it == _zoomRuleMap.end()) {
					return _emptyRules;
				}
				return it->second;
			}

		private:
			const int MAX_SUPPORTED_ZOOM_LEVEL = 32;

			const std::string _name;
			const float _opacity;
			const FilterMode _filterMode;
			const std::vector<std::shared_ptr<Rule>> _emptyRules;
			const std::vector<std::shared_ptr<Rule>> _rules;
			std::unordered_map<int, std::vector<std::shared_ptr<Rule>>> _zoomRuleMap;
		};
	}
}
