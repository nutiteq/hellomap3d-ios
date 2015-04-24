/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_LAYER_H_
#define _NUTI_MAPNIK_LAYER_H_

#include <string>
#include <vector>
#include <map>

namespace Nuti { namespace Mapnik {
	class Layer {
	public:
		explicit Layer(const std::string& name) : _name(name) { }

		const std::string& getName() const { return _name; }

		const std::vector<std::string>& getStyleNames() const { return _styleNames; }

		void clearStyleNames() {
			_styleNames.clear();
		}
			
		void addStyleName(const std::string& styleName) {
			_styleNames.push_back(styleName);
		}

		const std::map<std::string, std::string>& getDataSourceParameters() const { return _dataSourceParameters; }
			
		void clearDataSourceParameters() {
			_dataSourceParameters.clear();
		}
			
		void setDataSourceParameter(const std::string& id, const std::string& value) {
			_dataSourceParameters[id] = value;
		}

	private:
		const std::string _name;
		std::vector<std::string> _styleNames;
		std::map<std::string, std::string> _dataSourceParameters;
	};
} }

#endif
