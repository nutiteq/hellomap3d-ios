/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_VALUE_H_
#define _NUTI_MAPNIKVT_VALUE_H_

#include <string>

#include <boost/variant.hpp>

namespace Nuti { namespace MapnikVT {
    using Value = boost::variant<boost::blank, bool, long long, double, std::string>;
} }

#endif
