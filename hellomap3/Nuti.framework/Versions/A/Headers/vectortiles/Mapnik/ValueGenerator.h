#pragma once

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

namespace Nuti {
	namespace Mapnik {
		namespace phx = boost::phoenix;
		namespace karma = boost::spirit::karma;
		namespace ascii = boost::spirit::ascii;

		template <typename OutputIterator>
		struct ValueGenerator : karma::grammar<OutputIterator, Value(), ascii::space_type> {

			ValueGenerator() : ValueGenerator::base_type(value) {
				using karma::_pass;
				using karma::_val;
				using karma::_1;

				esc_char.add('\a', "\\a")('\b', "\\b")('\f', "\\f")('\n', "\\n")
							('\r', "\\r")('\t', "\\t")('\v', "\\v")('\\', "\\\\")
							('\'', "\\\'")('"', "\\\"");

				string %=
					'\'' << *(esc_char | karma::print | "\\x" << karma::hex) << '\'';

				value %=
					  karma::lit("null")		[_pass = phx::bind(&is_null_value, _val)]
					| karma::bool_				[_pass = phx::bind(&get_value<bool>, BOOL_VALUE, _val, _1)]
					| karma::long_long			[_pass = phx::bind(&get_value<long long>, LONG_VALUE, _val, _1)]
					| karma::double_			[_pass = phx::bind(&get_value<double>, DOUBLE_VALUE, _val, _1)]
					| string					[_pass = phx::bind(&get_value<std::string>, STRING_VALUE, _val, _1)]
					;
			}

			karma::symbols<char, const char *> esc_char;
			karma::rule<OutputIterator, std::string()> string;
			karma::rule<OutputIterator, Value(), ascii::space_type> value;

		private:
			static bool is_null_value(const Value& val) {
				return val.which() == NULL_VALUE;
			}

			template <typename T>
			static bool get_value(int type, const Value& val, T& result) {
				if (val.which() != type)
					return false;
				result = boost::get<T>(val);
				return true;
			}
		};
	}
}
