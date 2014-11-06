#pragma once

#include "UnaryExpression.h"
#include "BinaryExpression.h"
#include "TertiaryExpression.h"
#include "StringUtils.h"

#include <boost/lexical_cast.hpp>

namespace Nuti {
	namespace Mapnik {
		struct UpperCaseOperator : public UnaryExpression::Operator {
			virtual Value apply(const Value& val) const override {
				if (val.which() == STRING_VALUE) {
					return Value(toUpper(boost::get<std::string>(val)));
				}
				return Value();
			}
		};

		struct LowerCaseOperator : public UnaryExpression::Operator {
			virtual Value apply(const Value& val) const override {
				if (val.which() == STRING_VALUE) {
					return Value(toLower(boost::get<std::string>(val)));
				}
				return Value();
			}
		};

		struct CapitalizeOperator : public UnaryExpression::Operator {
			virtual Value apply(const Value& val) const override {
				if (val.which() == STRING_VALUE) {
					return Value(capitalize(boost::get<std::string>(val)));
				}
				return Value();
			}
		};

		template <typename Op>
		struct UnaryLogicalOperator : public UnaryExpression::Operator {
			virtual Value apply(const Value& val) const override {
				if (val.which() == BOOL_VALUE) {
					return Value(Op()(boost::get<bool>(val)));
				}
				return Value();
			}
		};

		using NotOperator = UnaryLogicalOperator<std::logical_not<bool>>;

		struct NegOperator : public UnaryExpression::Operator {
			virtual Value apply(const Value& val) const override {
				if (val.which() == LONG_VALUE) {
					return Value(-boost::get<long long>(val));
				}
				if (val.which() == DOUBLE_VALUE) {
					return Value(-boost::get<double>(val));
				}
				return Value();
			}
		};

		template <typename Op>
		struct BinaryLogicalOperator : public BinaryExpression::Operator {
			virtual Value apply(const Value& val1, const Value& val2) const override {
				if (val1.which() == BOOL_VALUE && val2.which() == BOOL_VALUE) {
					return Value(Op()(boost::get<bool>(val1), boost::get<bool>(val2)));
				}
				return Value();
			}
		};

		using AndOperator = BinaryLogicalOperator<std::logical_and<bool>>;

		using OrOperator = BinaryLogicalOperator<std::logical_or<bool>>;

		template <typename OpBool, typename OpLong, typename OpDouble, typename OpString, bool EqComparable>
		struct ComparisonOperator : public BinaryExpression::Operator {
			virtual Value apply(const Value& val1, const Value& val2) const override {
				if (val1.which() == val2.which()) {
					switch (val1.which()) {
					case NULL_VALUE:
						return EqComparable ? Value(true) : Value();
					case BOOL_VALUE:
						return Value(OpBool()(boost::get<bool>(val1), boost::get<bool>(val2)));
					case LONG_VALUE:
						return Value(OpLong()(boost::get<long long>(val1), boost::get<long long>(val2)));
					case DOUBLE_VALUE:
						return Value(OpDouble()(boost::get<double>(val1), boost::get<double>(val2)));
					case STRING_VALUE:
						return Value(OpString()(boost::get<std::string>(val1), boost::get<std::string>(val2)));
					}
				}
				if (val1.which() == NULL_VALUE || val2.which() == NULL_VALUE) {
					return Value();
				}
				if (val1.which() == STRING_VALUE || val2.which() == STRING_VALUE) {
					return Value(OpString()(boost::lexical_cast<std::string>(val1), boost::lexical_cast<std::string>(val2)));
				}
				if ((val1.which() == LONG_VALUE || val1.which() == DOUBLE_VALUE) && (val2.which() == LONG_VALUE || val2.which() == DOUBLE_VALUE)) {
					double arg1 = val1.which() == LONG_VALUE ? boost::get<long long>(val1) : boost::get<double>(val1);
					double arg2 = val2.which() == LONG_VALUE ? boost::get<long long>(val2) : boost::get<double>(val2);
					return Value(OpDouble()(arg1, arg2));
				}
				return Value();
			}
		};

		using GTOperator = ComparisonOperator<std::greater<bool>, std::greater<long long>, std::greater<double>, std::greater<std::string>, false>;

		using GTEOperator = ComparisonOperator<std::greater_equal<bool>, std::greater_equal<long long>, std::greater_equal<double>, std::greater_equal<std::string>, true>;

		using LTOperator = ComparisonOperator<std::less<bool>, std::less<long long>, std::less<double>, std::less<std::string>, false>;

		using LTEOperator = ComparisonOperator<std::less_equal<bool>, std::less_equal<long long>, std::less_equal<double>, std::less_equal<std::string>, true>;

		struct NEQOperator : public BinaryExpression::Operator {
			virtual Value apply(const Value& val1, const Value& val2) const override {
				if (val1.which() == val2.which()) {
					return Value(!(val1 == val2));
				}
				if (val1.which() == NULL_VALUE || val1.which() == STRING_VALUE || val2.which() == NULL_VALUE || val2.which() == STRING_VALUE) {
					return Value(true);
				}
				if ((val1.which() == LONG_VALUE || val1.which() == DOUBLE_VALUE) && (val2.which() == LONG_VALUE || val2.which() == DOUBLE_VALUE)) {
					double arg1 = val1.which() == LONG_VALUE ? boost::get<long long>(val1) : boost::get<double>(val1);
					double arg2 = val2.which() == LONG_VALUE ? boost::get<long long>(val2) : boost::get<double>(val2);
					return Value(arg1 != arg2);
				}
				return Value(true);
			}
		};

		struct EQOperator : public BinaryExpression::Operator {
			virtual Value apply(const Value& val1, const Value& val2) const override {
				if (val1.which() == val2.which()) {
					return Value(val1 == val2);
				}
				if (val1.which() == NULL_VALUE || val1.which() == STRING_VALUE || val2.which() == NULL_VALUE || val2.which() == STRING_VALUE) {
					return Value(false);
				}
				if ((val1.which() == LONG_VALUE || val1.which() == DOUBLE_VALUE) && (val2.which() == LONG_VALUE || val2.which() == DOUBLE_VALUE)) {
					double arg1 = val1.which() == LONG_VALUE ? boost::get<long long>(val1) : boost::get<double>(val1);
					double arg2 = val2.which() == LONG_VALUE ? boost::get<long long>(val2) : boost::get<double>(val2);
					return Value(arg1 == arg2);
				}
				return Value(false);
			}
		};

		template <typename OpLong, typename OpDouble>
		struct ArithmeticOperator : public BinaryExpression::Operator {
			virtual Value apply(const Value& val1, const Value& val2) const override {
				if (val1.which() == LONG_VALUE && val2.which() == LONG_VALUE) {
					long long arg1 = boost::get<long long>(val1);
					long long arg2 = boost::get<long long>(val2);
					return Value(OpLong()(arg1, arg2));
				}
				if ((val1.which() == LONG_VALUE || val1.which() == DOUBLE_VALUE) && (val2.which() == LONG_VALUE || val2.which() == DOUBLE_VALUE)) {
					double arg1 = val1.which() == LONG_VALUE ? boost::get<long long>(val1) : boost::get<double>(val1);
					double arg2 = val2.which() == LONG_VALUE ? boost::get<long long>(val2) : boost::get<double>(val2);
					return Value(OpDouble()(arg1, arg2));
				}
				return Value();
			}
		};

		using AddOperator = ArithmeticOperator<std::plus<long long>, std::plus<double>>;

		using SubOperator = ArithmeticOperator<std::minus<long long>, std::minus<double>>;

		using MulOperator = ArithmeticOperator<std::multiplies<long long>, std::multiplies<double>>;

		struct DivOperator : public BinaryExpression::Operator {
			virtual Value apply(const Value& val1, const Value& val2) const override {
				if (val1.which() == LONG_VALUE && val2.which() == LONG_VALUE) {
					long long arg1 = boost::get<long long>(val1);
					long long arg2 = boost::get<long long>(val2);
					if (arg2 == 0) {
						return Value();
					}
					return Value(arg1 / arg2);
				}
				if ((val1.which() == LONG_VALUE || val1.which() == DOUBLE_VALUE) && (val2.which() == LONG_VALUE || val2.which() == DOUBLE_VALUE)) {
					double arg1 = val1.which() == LONG_VALUE ? boost::get<long long>(val1) : boost::get<double>(val1);
					double arg2 = val2.which() == LONG_VALUE ? boost::get<long long>(val2) : boost::get<double>(val2);
					return Value(arg1 / arg2);
				}
				return Value();
			}
		};

		struct ModOperator : public BinaryExpression::Operator {
			virtual Value apply(const Value& val1, const Value& val2) const override {
				if (val1.which() == LONG_VALUE && val2.which() == LONG_VALUE) {
					long long arg1 = boost::get<long long>(val1);
					long long arg2 = boost::get<long long>(val2);
					if (arg2 == 0) {
						return Value();
					}
					return Value(arg1 % arg2);
				}
				if ((val1.which() == LONG_VALUE || val1.which() == DOUBLE_VALUE) && (val2.which() == LONG_VALUE || val2.which() == DOUBLE_VALUE)) {
					double arg1 = val1.which() == LONG_VALUE ? boost::get<long long>(val1) : boost::get<double>(val1);
					double arg2 = val2.which() == LONG_VALUE ? boost::get<long long>(val2) : boost::get<double>(val2);
					return Value(std::fmod(arg1, arg2));
				}
				return Value();
			}
		};

		struct MatchOperator : public BinaryExpression::Operator {
			virtual Value apply(const Value& val1, const Value& val2) const override {
				if (val1.which() == STRING_VALUE && val2.which() == STRING_VALUE) {
					return Value(regexMatch(boost::get<std::string>(val1), boost::get<std::string>(val2)));
				}
				return Value();
			}
		};

		struct ConcatenateOperator : public BinaryExpression::Operator {
			virtual Value apply(const Value& val1, const Value& val2) const override {
				std::string arg1;
				if (val1.which() == STRING_VALUE) {
					arg1 = boost::get<std::string>(val1);
				}
				else if (val1.which() != NULL_VALUE) {
					arg1 = boost::lexical_cast<std::string>(val1);
				}
				std::string arg2;
				if (val2.which() == STRING_VALUE) {
					arg2 = boost::get<std::string>(val2);
				}
				else if (val2.which() != NULL_VALUE) {
					arg2 = boost::lexical_cast<std::string>(val2);
				}
				return Value(arg1.append(arg2));
			}
		};

		struct ReplaceOperator : public TertiaryExpression::Operator {
			virtual Value apply(const Value& val1, const Value& val2, const Value& val3) const override {
				if (val1.which() == STRING_VALUE && val2.which() == STRING_VALUE && val3.which() == STRING_VALUE) {
					return Value(regexReplace(boost::get<std::string>(val1), boost::get<std::string>(val2), boost::get<std::string>(val3)));
				}
				return Value();
			}
		};
	}
}
