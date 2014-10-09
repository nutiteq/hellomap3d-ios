#pragma once

#include "Value.h"

#include <memory>
#include <functional>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace Nuti {
	namespace Mapnik {
		namespace phx = boost::phoenix;
		namespace qi = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;

		template <typename Iterator>
		struct ValueParser : qi::grammar<Iterator, Value(), ascii::space_type> {

			ValueParser() : ValueParser::base_type(value) {
				using qi::_val;
				using qi::_1;

				unesc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
							  ("\\r", '\r')("\\t", '\t')("\\v", '\v')("\\\\", '\\')
							  ("\\\'", '\'')("\\\"", '\"');

				string =
					'\'' >> *(unesc_char | "\\x" >> qi::hex | (qi::print - '\'')) >> '\'';

				value =
					  qi::lit("null")		[_val = phx::construct<Value>()]
					| qi::bool_				[_val = phx::construct<Value>(_1)]
					| qi::real_parser<double, qi::strict_real_policies<double>>() [_val = phx::construct<Value>(_1)]
					| qi::long_long			[_val = phx::construct<Value>(_1)]
					| string				[_val = phx::construct<Value>(_1)]
					;
			}

			qi::symbols<char const, char const> unesc_char;
			qi::rule<Iterator, std::string()> string;
			qi::rule<Iterator, Value(), ascii::space_type> value;
		};
	}
}
