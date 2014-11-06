#pragma once

#include <string>

#include <boost/variant.hpp>

namespace Nuti {
	namespace Mapnik {
		enum {
			NULL_VALUE = 0, BOOL_VALUE = 1, LONG_VALUE = 2, DOUBLE_VALUE = 3, STRING_VALUE = 4
		};

		using Value = boost::variant<boost::blank, bool, long long, double, std::string>;
	}
}
