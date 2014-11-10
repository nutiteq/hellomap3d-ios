#pragma once

#include "Filter.h"
#include "Symbolizer.h"

#include <memory>
#include <string>
#include <vector>

namespace Nuti {
	namespace Mapnik {
		class Rule {
		public:
			Rule(const std::string& name, float minScaleDenominator, float maxScaleDenominator, const std::shared_ptr<Filter>& filter, const std::vector<std::shared_ptr<Symbolizer>>& symbolizers) : _name(name), _minScaleDenominator(minScaleDenominator), _maxScaleDenominator(maxScaleDenominator), _filter(filter), _symbolizers(symbolizers) { }

			const std::string& getName() const { return _name; }
			float getMinScaleDenominator() const { return _minScaleDenominator; }
			float getMaxScaleDenominator() const { return _maxScaleDenominator; }
			const std::shared_ptr<Filter>& getFilter() const { return _filter; }
			const std::vector<std::shared_ptr<Symbolizer>>& getSymbolizers() const { return _symbolizers; }

		private:
			const std::string _name;
			const float _minScaleDenominator;
			const float _maxScaleDenominator;
			const std::shared_ptr<Filter> _filter;
			const std::vector<std::shared_ptr<Symbolizer>> _symbolizers;
		};
	}
}
