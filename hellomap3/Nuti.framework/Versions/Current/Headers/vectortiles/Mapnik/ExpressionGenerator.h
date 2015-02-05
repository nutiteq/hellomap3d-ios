/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_EXPRESSIONGENERATOR_H_
#define _NUTI_MAPNIK_EXPRESSIONGENERATOR_H_

#include "Value.h"
#include "Expression.h"
#include "Operators.h"
#include "ValueGenerator.h"

#include <memory>
#include <functional>

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/karma_alternative.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_function.hpp>

namespace Nuti { namespace Mapnik {
	namespace ExpressionGeneratorImpl {
		namespace phx = boost::phoenix;
		namespace karma = boost::spirit::karma;
		namespace ascii = boost::spirit::ascii;

		template <typename OutputIterator>
		struct Grammar : karma::grammar<OutputIterator, std::shared_ptr<Expression>(), ascii::space_type> {
			Grammar() : Grammar::base_type(expression) {
				using karma::_pass;
				using karma::_val;
				using karma::_1;
				using karma::_2;
				using karma::_3;

				identifier %=
					karma::string
					;

				variable =
					  identifier						[_pass = phx::bind(&getIdentifier, _val, _1)]
					| ('[' << variable << ']')			[_pass = phx::bind(&getVariableExpression, _val, _1)]
					| (variable << variable)			[_pass = phx::bind(&getBinaryExpression<ConcatenateOperator>, _val, _1, _2)]
					;

				expression =
					  (term0 << '?' << expression << ':' << expression) [_pass = phx::bind(&getTertiaryExpression<ConditionalOperator>, _val, _1, _2, _3)]
					| term0								[_1 = _val]
					;

				term0 =
					  (term0 << "and" << term1)			[_pass = phx::bind(&getBinaryExpression<AndOperator>, _val, _1, _2)]
					| (term0 << "or"  << term1)			[_pass = phx::bind(&getBinaryExpression<OrOperator>,  _val, _1, _2)]
					| term1								[_1 = _val]
					;

				term1 =
					  (term1 << "<>" << term2)			[_pass = phx::bind(&getBinaryExpression<NEQOperator>, _val, _1, _2)]
					| (term1 << "<=" << term2)			[_pass = phx::bind(&getBinaryExpression<LTEOperator>, _val, _1, _2)]
					| (term1 << ">=" << term2)			[_pass = phx::bind(&getBinaryExpression<GTEOperator>, _val, _1, _2)]
					| (term1 << "!=" << term2)			[_pass = phx::bind(&getBinaryExpression<NEQOperator>, _val, _1, _2)]
					| (term1 << '<'  << term2)			[_pass = phx::bind(&getBinaryExpression<LTOperator>,  _val, _1, _2)]
					| (term1 << '>'  << term2)			[_pass = phx::bind(&getBinaryExpression<GTOperator>,  _val, _1, _2)]
					| (term1 << '='  << term2)			[_pass = phx::bind(&getBinaryExpression<EQOperator>,  _val, _1, _2)]
					| term2								[_1 = _val]
					;

				term2 =
					  (term2 << '+' << term3)			[_pass = phx::bind(&getBinaryExpression<AddOperator>, _val, _1, _2)]
					| (term2 << '-' << term3)			[_pass = phx::bind(&getBinaryExpression<SubOperator>, _val, _1, _2)]
					| term3								[_1 = _val]
					;

				term3 =
					  (term3 << '*' << unary)			[_pass = phx::bind(&getBinaryExpression<MulOperator>, _val, _1, _2)]
					| (term3 << '/' << unary)			[_pass = phx::bind(&getBinaryExpression<DivOperator>, _val, _1, _2)]
					| (term3 << '%' << unary)			[_pass = phx::bind(&getBinaryExpression<ModOperator>, _val, _1, _2)]
					| unary								[_1 = _val]
					;

				unary =
					  ('-' << unary)					[_pass = phx::bind(&getUnaryExpression<NegOperator>, _val, _1)]
					| ('!' << unary)					[_pass = phx::bind(&getUnaryExpression<NotOperator>, _val, _1)]
					| postfix							[_1 = _val]
					;

				postfix =
					  (postfix << '.' << karma::lit("match")   << '(' << expression << ')') [_pass = phx::bind(&getBinaryExpression<MatchOperator>, _val, _1, _2)]
					| (postfix << '.' << karma::lit("replace") << '(' << expression << ',' << expression << ')') [_pass = phx::bind(&getTertiaryExpression<ReplaceOperator>, _val, _1, _2, _3)]
					| factor							[_1 = _val]
					;

				factor =
					  constant							[_pass = phx::bind(&getConstant, _val, _1)]
					| (karma::no_delimit['[' << variable] << ']') [_pass = phx::bind(&getVariableExpression, _val, _1)]
					| ('(' << expression << ')')		[_1 = _val]
					;
			}

			ValueGenerator<OutputIterator> constant;
			karma::rule<OutputIterator, std::string()> identifier;
			karma::rule<OutputIterator, std::shared_ptr<Expression>()> variable;
			karma::rule<OutputIterator, std::shared_ptr<Expression>(), ascii::space_type> expression, term0, term1, term2, term3, unary, postfix, factor;

		private:
			static bool getIdentifier(const std::shared_ptr<Expression>& expr, std::string& ident) {
				if (auto constExpr = std::dynamic_pointer_cast<ConstExpression>(expr)) {
					Value val = constExpr->getConstant();
					if (val.getType() == Value::Type::STRING_VALUE) {
						ident = val.getString();
						return true;
					}
				}
				return false;
			}

			static bool getConstant(const std::shared_ptr<Expression>& expr, Value& val) {
				if (auto constExpr = std::dynamic_pointer_cast<ConstExpression>(expr)) {
					val = constExpr->getConstant();
					return true;
				}
				return false;
			}

			static bool getVariableExpression(const std::shared_ptr<Expression>& expr, std::shared_ptr<Expression>& expr1) {
				if (auto varExpr = std::dynamic_pointer_cast<VariableExpression>(expr)) {
					expr1 = varExpr->getVariableExpression();
					return true;
				}
				return false;
			}

			template <typename Op>
			static bool getUnaryExpression(const std::shared_ptr<Expression>& expr, std::shared_ptr<Expression>& expr1) {
				if (auto unaryExpr = std::dynamic_pointer_cast<UnaryExpression>(expr)) {
					if (std::dynamic_pointer_cast<Op>(unaryExpr->getOperator())) {
						expr1 = unaryExpr->getExpression();
						return true;
					}
				}
				return false;
			}

			template <typename Op>
			static bool getBinaryExpression(const std::shared_ptr<Expression>& expr, std::shared_ptr<Expression>& expr1, std::shared_ptr<Expression>& expr2) {
				if (auto binaryExpr = std::dynamic_pointer_cast<BinaryExpression>(expr)) {
					if (std::dynamic_pointer_cast<Op>(binaryExpr->getOperator())) {
						expr1 = binaryExpr->getExpression(0);
						expr2 = binaryExpr->getExpression(1);
						return true;
					}
				}
				return false;
			}

			template <typename Op>
			static bool getTertiaryExpression(const std::shared_ptr<Expression>& expr, std::shared_ptr<Expression>& expr1, std::shared_ptr<Expression>& expr2, std::shared_ptr<Expression>& expr3) {
				if (auto tertiaryExpr = std::dynamic_pointer_cast<TertiaryExpression>(expr)) {
					if (std::dynamic_pointer_cast<Op>(tertiaryExpr->getOperator())) {
						expr1 = tertiaryExpr->getExpression(0);
						expr2 = tertiaryExpr->getExpression(1);
						expr3 = tertiaryExpr->getExpression(2);
						return true;
					}
				}
				return false;
			}
		};
	}

	template <typename Iterator> using ExpressionGenerator = ExpressionGeneratorImpl::Grammar<Iterator>;
} }

#endif