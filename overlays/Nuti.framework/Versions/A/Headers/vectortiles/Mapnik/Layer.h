#pragma once

#include <string>
#include <vector>
#include <map>

namespace Nuti {
	namespace Mapnik {
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
	}
}
