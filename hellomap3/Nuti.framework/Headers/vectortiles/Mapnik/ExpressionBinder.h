/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_EXPRESSIONBINDER_H_
#define _NUTI_MAPNIK_EXPRESSIONBINDER_H_

#include "Expression.h"
#include "ConstExpression.h"
#include "ExpressionContext.h"

#include <vector>
#include <memory>

#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>

namespace Nuti { namespace Mapnik {
	namespace ExpressionBinderImpl {
		template <typename V>
		struct Converter {
			static V convert(const Value& val) {
				switch (val.getType()) {
				case Value::Type::BOOL_VALUE:
					return static_cast<V>(val.getBool());
				case Value::Type::LONG_VALUE:
					return static_cast<V>(val.getLong());
				case Value::Type::DOUBLE_VALUE:
					return static_cast<V>(val.getDouble());
				case Value::Type::STRING_VALUE:
					return boost::lexical_cast<V>(val.getString());
				default:
					return V();
				}
			}
		};

		template <>
		struct Converter<bool> {
			static bool convert(const Value& val) {
				switch (val.getType()) {
				case Value::Type::BOOL_VALUE:
					return val.getBool();
				case Value::Type::LONG_VALUE:
					return val.getLong() != 0;
				case Value::Type::DOUBLE_VALUE:
					return val.getDouble() != 0;
				case Value::Type::STRING_VALUE:
					return boost::lexical_cast<bool>(val.getString());
				default:
					return false;
				}
			}
		};

		template <>
		struct Converter<std::string> {
			static std::string convert(const Value& val) {
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
		};

		struct Setter : public boost::static_visitor<> {
			Setter(const ExpressionContext& context) : _exprContext(context) { }

			template <typename V>
			void operator()(V & binding) const {
				Value val = binding.expr->evaluate(_exprContext);
				*binding.field = binding.convertFn(val);
			}

		private:
			const ExpressionContext& _exprContext;
		};
	}

	class ExpressionBinder {
	public:
		ExpressionBinder() = default;

		template <typename V>
		ExpressionBinder& bind(V* field, const std::shared_ptr<Expression>& expr) {
			if (auto constExpr = std::dynamic_pointer_cast<ConstExpression>(expr)) {
				*field = ExpressionBinderImpl::Converter<V>::convert(constExpr->getConstant());
			}
			else {
				_bindingMap.insert({ field, Binding<V>(field, expr, &ExpressionBinderImpl::Converter<V>::convert) });
			}
			return *this;
		}

		template <typename V>
		ExpressionBinder& bind(V* field, const std::shared_ptr<Expression>& expr, V (*convertFn)(const Value& val)) {
			if (auto constExpr = std::dynamic_pointer_cast<ConstExpression>(expr)) {
				*field = convertFn(constExpr->getConstant());
			}
			else {
				_bindingMap.insert({ field, Binding<V>(field, expr, convertFn) });
			}
			return *this;
		}

		void evaluate(const ExpressionContext& context) const {
			for (auto it = _bindingMap.begin(); it != _bindingMap.end(); it++) {
				const BindingVariant& binding = it->second;
				boost::apply_visitor(ExpressionBinderImpl::Setter(context), binding);
			}
		}

	private:
		template <typename V>
		struct Binding {
			V* field;
			std::shared_ptr<Expression> expr;
			V (*convertFn)(const Value&);

			Binding(V* field, std::shared_ptr<Expression> expr, V (*convertFn)(const Value&)) : field(field), expr(expr), convertFn(convertFn) { }
		};

		using BindingVariant = boost::variant<Binding<bool>, Binding<int>, Binding<unsigned int>, Binding<float>, Binding<std::string>>;

		std::map<void *, BindingVariant> _bindingMap;
	};
} }

#endif
