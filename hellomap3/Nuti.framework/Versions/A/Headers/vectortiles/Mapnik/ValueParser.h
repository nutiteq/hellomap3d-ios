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

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>

namespace Nuti { namespace Mapnik {
	namespace ValueParserImpl {
		namespace phx = boost::phoenix;
		namespace qi = boost::spirit::qi;
		namespace repo = boost::spirit::repository::qi;
		namespace encoding = boost::spirit::iso8859_1;

		template <typename Iterator>
		struct Grammar : qi::grammar<Iterator, Value()> {
			Grammar() : Grammar::base_type(value) {
				using qi::_val;
				using qi::_1;

				unesc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
								("\\r", '\r')("\\t", '\t')("\\v", '\v')("\\\\", '\\')
								("\\\'", '\'')("\\\"", '\"');

				null_kw = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["null"]];

				string =
					'\'' >> *(unesc_char | "\\x" >> qi::hex | (qi::print - '\'')) >> '\'';

				value =
					  null_kw				[_val = phx::construct<Value>()]
					| qi::bool_				[_val = phx::construct<Value>(_1)]
					| qi::real_parser<double, qi::strict_real_policies<double>>() [_val = phx::construct<Value>(_1)]
					| qi::long_long			[_val = phx::construct<Value>(_1)]
					| string				[_val = phx::construct<Value>(_1)]
					;
			}

			qi::symbols<char const, char const> unesc_char;
			qi::rule<Iterator, qi::unused_type()> null_kw;
			qi::rule<Iterator, std::string()> string;
			qi::rule<Iterator, Value()> value;
		};
	}

	template <typename Iterator> using ValueParser = ValueParserImpl::Grammar<Iterator>;
} }

#endif
