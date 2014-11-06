#pragma once

#include <string>
#include <vector>

namespace Nuti {
	namespace Mapnik {
		class FontSet {
		public:
			explicit FontSet(const std::string& name) : _name(name) { }

			const std::string& getName() const { return _name; }

			const std::vector<std::string>& getFaceNames() const { return _faceNames; }

			void clearFaceNames() {
				_faceNames.clear();
			}
			
			void addFaceName(const std::string& faceName) {
				_faceNames.push_back(faceName);
			}

		private:
			const std::string _name;
			std::vector<std::string> _faceNames;
		};
	}
}
