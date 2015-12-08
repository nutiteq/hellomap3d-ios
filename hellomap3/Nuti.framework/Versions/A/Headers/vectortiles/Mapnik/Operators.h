/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_OPERATORS_H_
#define _NUTI_MAPNIK_OPERATORS_H_

#include "Expression.h"
#include "StringUtils.h"
#include "ValueConverter.h"

namespace Nuti { namespace Mapnik {
	struct UpperCaseOperator : public UnaryExpression::Operator {
		virtual Value apply(const Value& val) const override {
			if (val.getType() == Value::Type::STRING_VALUE) {
				return Value(toUpper(val.getString()));
			}
			return Value();
		}
	};

	struct LowerCaseOperator : public UnaryExpression::Operator {
		virtual Value apply(const Value& val) const override {
			if (val.getType() == Value::Type::STRING_VALUE) {
				return Value(toLower(val.getString()));
			}
			return Value();
		}
	};

	struct CapitalizeOperator : public UnaryExpression::Operator {
		virtual Value apply(const Value& val) const override {
			if (val.getType() == Value::Type::STRING_VALUE) {
				return Value(capitalize(val.getString()));
			}
			return Value();
		}
	};

	template <typename Op>
	struct UnaryLogicalOperator : public UnaryExpression::Operator {
		virtual Value apply(const Value& val) const override {
			if (val.getType() == Value::Type::BOOL_VALUE) {
				return Value(Op()(val.getBool()));
			}
			return Value();
		}
	};

	using NotOperator = UnaryLogicalOperator<std::logical_not<bool>>;

	struct NegOperator : public UnaryExpression::Operator {
		virtual Value apply(const Value& val) const override {
			if (val.getType() == Value::Type::LONG_VALUE) {
				return Value(-val.getLong());
			}
			if (val.getType() == Value::Type::DOUBLE_VALUE) {
				return Value(-val.getDouble());
			}
			return Value();
		}
	};

	template <typename Op>
	struct BinaryLogicalOperator : public BinaryExpression::Operator {
		virtual Value apply(const Value& val1, const Value& val2) const override {
			if (val1.getType() == Value::Type::BOOL_VALUE && val2.getType() == Value::Type::BOOL_VALUE) {
				return Value(Op()(val1.getBool(), val2.getBool()));
			}
			return Value();
		}
	};

	using AndOperator = BinaryLogicalOperator<std::logical_and<bool>>;

	using OrOperator = BinaryLogicalOperator<std::logical_or<bool>>;

	template <typename OpBool, typename OpLong, typename OpDouble, typename OpString, bool EqComparable>
	struct ComparisonOperator : public BinaryExpression::Operator {
		virtual Value apply(const Value& val1, const Value& val2) const override {
			if (val1.getType() == val2.getType()) {
				switch (val1.getType()) {
				case Value::Type::NULL_VALUE:
					return EqComparable ? Value(true) : Value();
				case Value::Type::BOOL_VALUE:
					return Value(OpBool()(val1.getBool(), val2.getBool()));
				case Value::Type::LONG_VALUE:
					return Value(OpLong()(val1.getLong(), val2.getLong()));
				case Value::Type::DOUBLE_VALUE:
					return Value(OpDouble()(val1.getDouble(), val2.getDouble()));
				case Value::Type::STRING_VALUE:
					return Value(OpString()(val1.getString(), val2.getString()));
				}
			}
			if (val1.getType() == Value::Type::NULL_VALUE || val2.getType() == Value::Type::NULL_VALUE) {
				return Value();
			}
			if (val1.getType() == Value::Type::STRING_VALUE || val2.getType() == Value::Type::STRING_VALUE) {
                std::string arg1 = ValueConverter<std::string>::convert(val1);
                std::string arg2 = ValueConverter<std::string>::convert(val2);
				return Value(OpString()(arg1, arg2));
			}
			if ((val1.getType() == Value::Type::LONG_VALUE || val1.getType() == Value::Type::DOUBLE_VALUE) && (val2.getType() == Value::Type::LONG_VALUE || val2.getType() == Value::Type::DOUBLE_VALUE)) {
				double arg1 = val1.getType() == Value::Type::LONG_VALUE ? val1.getLong() : val1.getDouble();
				double arg2 = val2.getType() == Value::Type::LONG_VALUE ? val2.getLong() : val2.getDouble();
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
			if (val1.getType() == val2.getType()) {
				return Value(!(val1 == val2));
			}
			if (val1.getType() == Value::Type::NULL_VALUE || val1.getType() == Value::Type::STRING_VALUE || val2.getType() == Value::Type::NULL_VALUE || val2.getType() == Value::Type::STRING_VALUE) {
				return Value(true);
			}
			if ((val1.getType() == Value::Type::LONG_VALUE || val1.getType() == Value::Type::DOUBLE_VALUE) && (val2.getType() == Value::Type::LONG_VALUE || val2.getType() == Value::Type::DOUBLE_VALUE)) {
				double arg1 = val1.getType() == Value::Type::LONG_VALUE ? val1.getLong() : val1.getDouble();
				double arg2 = val2.getType() == Value::Type::LONG_VALUE ? val2.getLong() : val2.getDouble();
				return Value(arg1 != arg2);
			}
			return Value(true);
		}
	};

	struct EQOperator : public BinaryExpression::Operator {
		virtual Value apply(const Value& val1, const Value& val2) const override {
			if (val1.getType() == val2.getType()) {
				return Value(val1 == val2);
			}
			if (val1.getType() == Value::Type::NULL_VALUE || val1.getType() == Value::Type::STRING_VALUE || val2.getType() == Value::Type::NULL_VALUE || val2.getType() == Value::Type::STRING_VALUE) {
				return Value(false);
			}
			if ((val1.getType() == Value::Type::LONG_VALUE || val1.getType() == Value::Type::DOUBLE_VALUE) && (val2.getType() == Value::Type::LONG_VALUE || val2.getType() == Value::Type::DOUBLE_VALUE)) {
				double arg1 = val1.getType() == Value::Type::LONG_VALUE ? val1.getLong() : val1.getDouble();
				double arg2 = val2.getType() == Value::Type::LONG_VALUE ? val2.getLong() : val2.getDouble();
				return Value(arg1 == arg2);
			}
			return Value(false);
		}
	};

	template <typename OpLong, typename OpDouble>
	struct ArithmeticOperator : public BinaryExpression::Operator {
		virtual Value apply(const Value& val1, const Value& val2) const override {
			if (val1.getType() == Value::Type::LONG_VALUE && val2.getType() == Value::Type::LONG_VALUE) {
				long long arg1 = val1.getLong();
				long long arg2 = val2.getLong();
				return Value(OpLong()(arg1, arg2));
			}
			if ((val1.getType() == Value::Type::LONG_VALUE || val1.getType() == Value::Type::DOUBLE_VALUE) && (val2.getType() == Value::Type::LONG_VALUE || val2.getType() == Value::Type::DOUBLE_VALUE)) {
				double arg1 = val1.getType() == Value::Type::LONG_VALUE ? val1.getLong() : val1.getDouble();
				double arg2 = val2.getType() == Value::Type::LONG_VALUE ? val2.getLong() : val2.getDouble();
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
			if (val1.getType() == Value::Type::LONG_VALUE && val2.getType() == Value::Type::LONG_VALUE) {
				long long arg1 = val1.getLong();
				long long arg2 = val2.getLong();
				if (arg2 == 0) {
					return Value();
				}
				return Value(arg1 / arg2);
			}
			if ((val1.getType() == Value::Type::LONG_VALUE || val1.getType() == Value::Type::DOUBLE_VALUE) && (val2.getType() == Value::Type::LONG_VALUE || val2.getType() == Value::Type::DOUBLE_VALUE)) {
				double arg1 = val1.getType() == Value::Type::LONG_VALUE ? val1.getLong() : val1.getDouble();
				double arg2 = val2.getType() == Value::Type::LONG_VALUE ? val2.getLong() : val2.getDouble();
				return Value(arg1 / arg2);
			}
			return Value();
		}
	};

	struct ModOperator : public BinaryExpression::Operator {
		virtual Value apply(const Value& val1, const Value& val2) const override {
			if (val1.getType() == Value::Type::LONG_VALUE && val2.getType() == Value::Type::LONG_VALUE) {
				long long arg1 = val1.getLong();
				long long arg2 = val2.getLong();
				if (arg2 == 0) {
					return Value();
				}
				return Value(arg1 % arg2);
			}
			if ((val1.getType() == Value::Type::LONG_VALUE || val1.getType() == Value::Type::DOUBLE_VALUE) && (val2.getType() == Value::Type::LONG_VALUE || val2.getType() == Value::Type::DOUBLE_VALUE)) {
				double arg1 = val1.getType() == Value::Type::LONG_VALUE ? val1.getLong() : val1.getDouble();
				double arg2 = val2.getType() == Value::Type::LONG_VALUE ? val2.getLong() : val2.getDouble();
				return Value(std::fmod(arg1, arg2));
			}
			return Value();
		}
	};

	struct MatchOperator : public BinaryExpression::Operator {
		virtual Value apply(const Value& val1, const Value& val2) const override {
            std::string arg1 = ValueConverter<std::string>::convert(val1);
            std::string arg2 = ValueConverter<std::string>::convert(val2);
            return Value(regexMatch(arg1, arg2));
		}
	};

	struct ConcatenateOperator : public BinaryExpression::Operator {
		virtual Value apply(const Value& val1, const Value& val2) const override {
            std::string arg1 = ValueConverter<std::string>::convert(val1);
            std::string arg2 = ValueConverter<std::string>::convert(val2);
			return Value(arg1.append(arg2));
		}
	};

	struct ReplaceOperator : public TertiaryExpression::Operator {
		virtual Value apply(const Value& val1, const Value& val2, const Value& val3) const override {
            std::string arg1 = ValueConverter<std::string>::convert(val1);
            std::string arg2 = ValueConverter<std::string>::convert(val2);
            std::string arg3 = ValueConverter<std::string>::convert(val3);
            return Value(regexReplace(arg1, arg2, arg3));
		}
	};

	struct ConditionalOperator : public TertiaryExpression::Operator {
		virtual Value apply(const Value& val1, const Value& val2, const Value& val3) const override {
			if (val1.getType() == Value::Type::BOOL_VALUE) {
				return val1.getBool() ? val2 : val3;
			}
			return Value();
		}
	};
} }

#endif
