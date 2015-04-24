/*
* Copyright 2014 Nutiteq Llc. All rights reserved.
* Copying and using this code is allowed only according
* to license terms, as given in https://www.nutiteq.com/license/
*/

#ifndef _NUTI_MAPNIK_VALUECONVERTER_H_
#define _NUTI_MAPNIK_VALUECONVERTER_H_

#include "Value.h"

#include <boost/lexical_cast.hpp>

namespace Nuti { namespace Mapnik {

	template <typename V>
	struct ValueConverter {
		static V convert(const Value& val) {
			switch (val.getType()) {
			case Value::Type::BOOL_VALUE:
				return static_cast<V>(val.getBool());
			case Value::Type::LONG_VALUE:
				return static_cast<V>(val.getLong());
			case Value::Type::DOUBLE_VALUE:
				return static_cast<V>(val.getDouble());
			case Value::Type::STRING_VALUE:
				try {
					return boost::lexical_cast<V>(val.getString());
				}
				catch (const boost::bad_lexical_cast&) {
					return V();
				}
			default:
				return V();
			}
		}
	};

	template <>
	struct ValueConverter<bool> {
		static bool convert(const Value& val) {
			switch (val.getType()) {
			case Value::Type::BOOL_VALUE:
				return val.getBool();
			case Value::Type::LONG_VALUE:
				return val.getLong() != 0;
			case Value::Type::DOUBLE_VALUE:
				return val.getDouble() != 0;
			case Value::Type::STRING_VALUE:
				try {
					if (val.getString() == "true") {
						return true;
					}
					if (val.getString() == "false") {
						return false;
					}
					return boost::lexical_cast<bool>(val.getString());
				}
				catch (const boost::bad_lexical_cast&) {
					return false;
				}
			default:
				return false;
			}
		}
	};

	template <>
	struct ValueConverter<std::string> {
		static std::string convert(const Value& val) {
			try {
				switch (val.getType()) {
				case Value::Type::BOOL_VALUE:
					return boost::lexical_cast<std::string>(val.getBool());
				case Value::Type::LONG_VALUE:
					return boost::lexical_cast<std::string>(val.getLong());
				case Value::Type::DOUBLE_VALUE:
					return boost::lexical_cast<std::string>(val.getDouble());
				case Value::Type::STRING_VALUE:
					return val.getString();
				default:
					return std::string();
				}
			}
			catch (const boost::bad_lexical_cast&) {
				return std::string();
			}
		}
	};

} }

#endif
