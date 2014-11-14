/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_EXPRESSIONPARSER_H_
#define _NUTI_MAPNIK_EXPRESSIONPARSER_H_

#include "Value.h"
#include "Expression.h"
#include "ConstExpression.h"
#include "VariableExpression.h"
#include "BinaryExpression.h"
#include "TertiaryExpression.h"
#include "Operators.h"
#include "ValueParser.h"

#include <memory>
#include <functional>
#include <typeinfo>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/repository/include/qi_distinct.hpp>

namespace Nuti { namespace Mapnik {
	namespace ExpressionParserImpl {
		namespace phx = boost::phoenix;
		namespace qi = boost::spirit::qi;
		namespace repo = boost::spirit::repository::qi;
		namespace ascii = boost::spirit::ascii;
		
		template <typename Iterator>
		struct Grammar : qi::grammar<Iterator, std::shared_ptr<Expression>(), ascii::space_type> {
			Grammar() : Grammar::base_type(expression) {
				using qi::_val;
				using qi::_1;
				using qi::_2;

				le_kw  = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["le"]];
				ge_kw  = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["ge"]];
				lt_kw  = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["lt"]];
				gt_kw  = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["gt"]];
				eq_kw  = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["eq"]];
				neq_kw = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["neq"]];
				or_kw  = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["or"]];
				and_kw = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["and"]];
				not_kw = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["not"]];
				match_kw = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["match"]];
				replace_kw = repo::distinct(qi::char_("a-zA-Z0-9_"))[qi::no_case["replace"]];

				identifier %=
					qi::lexeme[qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z0-9_")] >> -(qi::string("::") >> identifier)
					;

				variable =
					( (identifier									 [_val = phx::bind(&makeIdentifierExpression, _1)])
					| ('[' >> variable >> ']')						 [_val = phx::bind(&makeVariableExpression, _1)]
					)
					>> -(variable									 [_val = phx::bind(&makeBinaryExpression<ConcatenateOperator>, _val, _1)])
					;

				expression =
					term0											 [_val = _1]
					>> -( (qi::lit('?') >> expression >> ':' >> expression) [_val = phx::bind(&makeTertiaryExpression<ConditionalOperator>, _val, _1, _2)]
					    )
					;

				term0 =
					term1											 [_val = _1]
					>> *( ((qi::lit("&&") | and_kw) >> term1)		 [_val = phx::bind(&makeBinaryExpression<AndOperator>, _val, _1)]
						| ((qi::lit("||") | or_kw) >> term1)		 [_val = phx::bind(&makeBinaryExpression<OrOperator>,  _val, _1)]
						)
					;

				term1 =
					term2											 [_val = _1]
					>> *( ((qi::lit("<>") | "!=" | neq_kw) >> term2) [_val = phx::bind(&makeBinaryExpression<NEQOperator>, _val, _1)]
						| ((qi::lit("<=") | le_kw        ) >> term2) [_val = phx::bind(&makeBinaryExpression<LTEOperator>, _val, _1)]
						| ((qi::lit(">=") | ge_kw        ) >> term2) [_val = phx::bind(&makeBinaryExpression<GTEOperator>, _val, _1)]
						| ((qi::lit('<' ) | lt_kw        ) >> term2) [_val = phx::bind(&makeBinaryExpression<LTOperator>,  _val, _1)]
						| ((qi::lit('>' ) | gt_kw        ) >> term2) [_val = phx::bind(&makeBinaryExpression<GTOperator>,  _val, _1)]
						| ((qi::lit('=' ) | eq_kw        ) >> term2) [_val = phx::bind(&makeBinaryExpression<EQOperator>,  _val, _1)]
						)
					;

				term2 =
					term3											 [_val = _1]
					>> *( (qi::lit("+") >> term3)					 [_val = phx::bind(&makeBinaryExpression<AddOperator>, _val, _1)]
						| (qi::lit("-") >> term3)					 [_val = phx::bind(&makeBinaryExpression<SubOperator>, _val, _1)]
						)
					;

				term3 =
					unary											 [_val = _1]
					>> *( (qi::lit("*") >> unary)					 [_val = phx::bind(&makeBinaryExpression<MulOperator>, _val, _1)]
						| (qi::lit("/") >> unary)					 [_val = phx::bind(&makeBinaryExpression<DivOperator>, _val, _1)]
						| (qi::lit("%") >> unary)					 [_val = phx::bind(&makeBinaryExpression<ModOperator>, _val, _1)]
						)
					;

				unary =
						postfix										 [_val = _1]
					|  (qi::lit('-')            >> unary)			 [_val = phx::bind(&makeUnaryExpression<NegOperator>, _1)]
					| ((qi::lit('!') || not_kw) >> unary)			 [_val = phx::bind(&makeUnaryExpression<NotOperator>, _1)]
					;

				postfix =
					factor											 [_val = _1]
					>> *('.' >> ( (match_kw   >> '(' >> expression >> ')') [_val = phx::bind(&makeBinaryExpression<MatchOperator>, _val, _1)]
								| (replace_kw >> '(' >> expression >> ',' >> expression >> ')') [_val = phx::bind(&makeTertiaryExpression<ReplaceOperator>, _val, _1, _2)]
								)
						)
					;

				factor =
					  constant										 [_val = phx::bind(&makeConstExpression, _1)]
					| ('[' >> variable >> ']')						 [_val = phx::bind(&makeVariableExpression, _1)]
					| ('(' >> expression >> ')')					 [_val = _1]
					;
			}

			ValueParser<Iterator> constant;
			qi::rule<Iterator, qi::unused_type()> not_kw, and_kw, or_kw, neq_kw, eq_kw, le_kw, ge_kw, lt_kw, gt_kw, match_kw, replace_kw;
			qi::rule<Iterator, std::string()> identifier;
			qi::rule<Iterator, std::shared_ptr<Expression>()> variable;
			qi::rule<Iterator, std::shared_ptr<Expression>(), ascii::space_type> expression, term0, term1, term2, term3, unary, postfix, factor;

		private:
			static std::shared_ptr<Expression> makeIdentifierExpression(const std::string& ident) {
				return std::make_shared<ConstExpression>(Value(ident));
			}

			static std::shared_ptr<Expression> makeConstExpression(const Value& val) {
				return std::make_shared<ConstExpression>(val);
			}

			static std::shared_ptr<Expression> makeVariableExpression(const std::shared_ptr<Expression>& expr) {
				return std::make_shared<VariableExpression>(expr);
			}

			template <typename Op>
			static std::shared_ptr<Expression> makeUnaryExpression(const std::shared_ptr<Expression>& expr) {
				return std::make_shared<UnaryExpression>(std::make_shared<Op>(), expr);
			}

			template <typename Op>
			static std::shared_ptr<Expression> makeBinaryExpression(const std::shared_ptr<Expression>& expr1, const std::shared_ptr<Expression>& expr2) {
				auto op = std::make_shared<Op>();
				if (typeid(Op) == typeid(OrOperator)) {
					return std::make_shared<BinaryOrExpression>(op, expr1, expr2);
				}
				if (typeid(Op) == typeid(AndOperator)) {
					return std::make_shared<BinaryAndExpression>(op, expr1, expr2);
				}
				return std::make_shared<BinaryExpression>(op, expr1, expr2);
			}

			template <typename Op>
			static std::shared_ptr<Expression> makeTertiaryExpression(const std::shared_ptr<Expression>& expr1, const std::shared_ptr<Expression>& expr2, const std::shared_ptr<Expression>& expr3) {
				return std::make_shared<TertiaryExpression>(std::make_shared<Op>(), expr1, expr2, expr3);
			}
		};
	}

	template <typename Iterator> using ExpressionParser = ExpressionParserImpl::Grammar<Iterator>;
} }

#endif
