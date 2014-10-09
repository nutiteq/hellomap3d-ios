#pragma once

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

namespace Nuti {
	namespace Mapnik {
		namespace phx = boost::phoenix;
		namespace qi = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;
		
		template <typename Iterator>
		struct ExpressionParser : qi::grammar<Iterator, std::shared_ptr<Expression>(), ascii::space_type> {

			ExpressionParser() : ExpressionParser::base_type(expression) {
				using qi::_val;
				using qi::_1;
				using qi::_2;

				identifier %=
					qi::lexeme[qi::char_("a-zA-Z_") >> *qi::char_("a-zA-Z0-9_")] >> -(qi::string("::") >> identifier)
					;
				
				expression =
					term1											[_val = _1]
					>> *( ((qi::lit("&&") | "and") >> term1)		[_val = phx::bind(&makeBinaryExpression<AndOperator>, _val, _1)]
						| ((qi::lit("||") | "or" ) >> term1)		[_val = phx::bind(&makeBinaryExpression<OrOperator>,  _val, _1)]
						)
					;

				term1 =
					term2											[_val = _1]
					>> *( ((qi::lit("<>") | "!=" | "neq") >> term2)	[_val = phx::bind(&makeBinaryExpression<NEQOperator>, _val, _1)]
						| ((qi::lit("<=") | "le"        ) >> term2)	[_val = phx::bind(&makeBinaryExpression<LTEOperator>, _val, _1)]
						| ((qi::lit(">=") | "ge"        ) >> term2)	[_val = phx::bind(&makeBinaryExpression<GTEOperator>, _val, _1)]
						| ((qi::lit('<' ) | "lt"        ) >> term2)	[_val = phx::bind(&makeBinaryExpression<LTOperator>,  _val, _1)]
						| ((qi::lit('>' ) | "gt"        ) >> term2)	[_val = phx::bind(&makeBinaryExpression<GTOperator>,  _val, _1)]
						| ((qi::lit('=' ) | "eq"        ) >> term2)	[_val = phx::bind(&makeBinaryExpression<EQOperator>,  _val, _1)]
						)
					;

				term2 =
					term3											[_val = _1]
					>> *( (qi::lit("+") >> term3)					[_val = phx::bind(&makeBinaryExpression<AddOperator>, _val, _1)]
						| (qi::lit("-") >> term3)					[_val = phx::bind(&makeBinaryExpression<SubOperator>, _val, _1)]
						)
					;

				term3 =
					unary											[_val = _1]
					>> *( (qi::lit("*") >> unary)					[_val = phx::bind(&makeBinaryExpression<MulOperator>, _val, _1)]
						| (qi::lit("/") >> unary)					[_val = phx::bind(&makeBinaryExpression<DivOperator>, _val, _1)]
						| (qi::lit("%") >> unary)					[_val = phx::bind(&makeBinaryExpression<ModOperator>, _val, _1)]
						)
					;

				unary =
					  postfix										[_val = _1]
					|  (qi::lit('-')           >> unary)			[_val = phx::bind(&makeUnaryExpression<NegOperator>, _1)]
					| ((qi::lit('!') || "not") >> unary)			[_val = phx::bind(&makeUnaryExpression<NotOperator>, _1)]
					;

				postfix =
					factor											[_val = _1]
					>> *('.' >> ( (qi::lit("match")   >> '(' >> expression >> ')') [_val = phx::bind(&makeBinaryExpression<MatchOperator>, _val, _1)]
								| (qi::lit("replace") >> '(' >> expression >> ',' >> expression >> ')') [_val = phx::bind(&makeTertiaryExpression<ReplaceOperator>, _val, _1, _2)]
								)
						)
					;

				factor =
					  constant										[_val = phx::bind(&makeConstExpression, _1)]
					| ('[' >> identifier >> ']')					[_val = phx::bind(&makeVariableExpression, _1)]
					| ('(' >> expression >> ')')					[_val = _1]
					;
			}

			ValueParser<Iterator> constant;
			qi::rule<Iterator, std::string()> identifier;
			qi::rule<Iterator, std::shared_ptr<Expression>(), ascii::space_type> expression, term1, term2, term3, unary, postfix, factor;

		private:
			static std::string makeIdentifier(const std::vector<std::string>& identVec) {
				std::string ident;
				for (std::size_t i = 0; i < identVec.size(); i++) {
					if (i != 0) {
						ident += "::";
					}
					ident += identVec[i];
				}
			}

			static std::shared_ptr<Expression> makeConstExpression(const Value& val) {
				return std::static_pointer_cast<Expression>(std::make_shared<ConstExpression>(val));
			}

			static std::shared_ptr<Expression> makeVariableExpression(const std::string& name) {
				return std::static_pointer_cast<Expression>(std::make_shared<VariableExpression>(name));
			}

			template <typename Op>
			static std::shared_ptr<Expression> makeUnaryExpression(const std::shared_ptr<Expression>& expr) {
				auto op = std::static_pointer_cast<UnaryExpression::Operator>(std::make_shared<Op>());
				return std::static_pointer_cast<Expression>(std::make_shared<UnaryExpression>(op, expr));
			}

			template <typename Op>
			static std::shared_ptr<Expression> makeBinaryExpression(const std::shared_ptr<Expression>& expr1, const std::shared_ptr<Expression>& expr2) {
				auto op = std::static_pointer_cast<BinaryExpression::Operator>(std::make_shared<Op>());
				if (typeid(Op) == typeid(OrOperator)) {
					return std::static_pointer_cast<Expression>(std::make_shared<BinaryOrExpression>(op, expr1, expr2));
				}
				if (typeid(Op) == typeid(AndOperator)) {
					return std::static_pointer_cast<Expression>(std::make_shared<BinaryAndExpression>(op, expr1, expr2));
				}
				return std::static_pointer_cast<Expression>(std::make_shared<BinaryExpression>(op, expr1, expr2));
			}

			template <typename Op>
			static std::shared_ptr<Expression> makeTertiaryExpression(const std::shared_ptr<Expression>& expr1, const std::shared_ptr<Expression>& expr2, const std::shared_ptr<Expression>& expr3) {
				auto op = std::static_pointer_cast<TertiaryExpression::Operator>(std::make_shared<Op>());
				return std::static_pointer_cast<Expression>(std::make_shared<TertiaryExpression>(op, expr1, expr2, expr3));
			}
		};
	}
}
