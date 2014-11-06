#pragma once

#include <string>

namespace Nuti {
	namespace Mapnik {
		std::string toUpper(const std::string& str);
		std::string toLower(const std::string& str);
		std::string capitalize(const std::string& str);
		bool regexMatch(const std::string& str, const std::string& re);
		std::string regexReplace(const std::string& str, const std::string& re, const std::string& replacement);
	}
}
