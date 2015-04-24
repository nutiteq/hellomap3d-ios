/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_VALUEPARSER_H_
#define _NUTI_MAPNIK_VALUEPARSER_H_

#include "Value.h"

#include <memory>
#include <functional>

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/karma_symbols.hpp>
#include <boost/spirit/include/karma_alternative.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

namespace Nuti { namespace Mapnik {
	namespace ValueGeneratorImpl {
		namespace phx = boost::phoenix;
		namespace karma = boost::spirit::karma;
		namespace ascii = boost::spirit::ascii;

		template <typename OutputIterator>
		struct Grammar : karma::grammar<OutputIterator, Value()> {
			Grammar() : Grammar::base_type(value) {
				using karma::_pass;
				using karma::_val;
				using karma::_1;

				esc_char.add('\a', "\\a")('\b', "\\b")('\f', "\\f")('\n', "\\n")
							('\r', "\\r")('\t', "\\t")('\v', "\\v")('\\', "\\\\")
							('\'', "\\\'")('"', "\\\"");

				string %=
					'\'' << *(esc_char | karma::print | "\\x" << karma::hex) << '\'';

				value %=
					  karma::lit("null")		[_pass = phx::bind(&isNullValue, _val)]
					| karma::bool_				[_pass = phx::bind(&getBoolValue, _val, _1)]
					| karma::long_long			[_pass = phx::bind(&getLongValue, _val, _1)]
					| karma::double_			[_pass = phx::bind(&getDoubleValue, _val, _1)]
					| string					[_pass = phx::bind(&getStringValue, _val, _1)]
					;
			}

			karma::symbols<char, const char *> esc_char;
			karma::rule<OutputIterator, std::string()> string;
			karma::rule<OutputIterator, Value()> value;

		private:
			static bool isNullValue(const Value& val) {
				return val.getType() == Value::Type::NULL_VALUE;
			}

			static bool getBoolValue(const Value& val, bool& result) {
				if (val.getType() != Value::Type::BOOL_VALUE) return false; result = val.getBool(); return true;
			}

			static bool getLongValue(Value::Type type, const Value& val, long long& result) {
				if (val.getType() != Value::Type::LONG_VALUE) return false; result = val.getLong(); return true;
			}

			static bool getDoubleValue(Value::Type type, const Value& val, double& result) {
				if (val.getType() != Value::Type::DOUBLE_VALUE) return false; result = val.getDouble(); return true;
			}

			static bool getStringValue(Value::Type type, const Value& val, std::string& result) {
				if (val.getType() != Value::Type::STRING_VALUE) return false; result = val.getString(); return true;
			}
		};
	}

	template <typename Iterator> using ValueGenerator = ValueGeneratorImpl::Grammar<Iterator>;
} }

#endif
