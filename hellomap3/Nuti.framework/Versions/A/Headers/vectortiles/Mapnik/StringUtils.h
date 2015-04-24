/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_STRINGUTILS_H_
#define _NUTI_MAPNIK_STRINGUTILS_H_

#include <string>

namespace Nuti { namespace Mapnik {
	std::string toUpper(const std::string& str);
	std::string toLower(const std::string& str);
	std::string capitalize(const std::string& str);
	bool regexMatch(const std::string& str, const std::string& re);
	std::string regexReplace(const std::string& str, const std::string& re, const std::string& replacement);
} }

#endif
