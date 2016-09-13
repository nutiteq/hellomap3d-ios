/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_CARTOCSS_VALUE_H_
#define _NUTI_CARTOCSS_VALUE_H_

#include "Color.h"

#include <string>
#include <vector>
#include <ostream>

#include <boost/lexical_cast.hpp>
#include <boost/variant.hpp>

namespace Nuti { namespace CartoCSS {
    using Value = boost::make_recursive_variant<boost::blank, bool, long long, double, Color, std::string, std::vector<boost::recursive_variant_>>::type;

    inline std::ostream& operator << (std::ostream& os, const std::vector<Value>& values) {
        for (std::size_t i = 0; i < values.size(); i++) {
            if (i > 0) {
                os << ",";
            }
            os << values[i];
        }
        return os;
    }
} }

#endif
