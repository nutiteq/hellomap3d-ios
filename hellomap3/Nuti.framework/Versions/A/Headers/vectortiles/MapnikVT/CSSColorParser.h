/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_CSSCOLORPARSER_H_
#define _NUTI_MAPNIKVT_CSSCOLORPARSER_H_

#include <string>

namespace Nuti { namespace MapnikVT {
    bool parseCSSColor(std::string name, unsigned int& value);
} }

#endif
