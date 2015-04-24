/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_EXPRESSIONBINDER_H_
#define _NUTI_MAPNIK_EXPRESSIONBINDER_H_

#include "Expression.h"
#include "ExpressionContext.h"
#include "ValueConverter.h"

#include <vector>
#include <memory>

#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>

#include <cglib/mat.h>

namespace Nuti { namespace Mapnik {
	namespace ExpressionBinderImpl {
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
				*field = ValueConverter<V>::convert(constExpr->getConstant());
			}
			else {
				_bindingMap.insert({ field, Binding<V>(field, expr, &ValueConverter<V>::convert) });
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

		using BindingVariant = boost::variant<Binding<bool>, Binding<int>, Binding<unsigned int>, Binding<float>, Binding<std::string>, Binding<cglib::mat3x3<float>>, Binding<boost::optional<cglib::mat3x3<float>>>>;

		std::map<void *, BindingVariant> _bindingMap;
	};
} }

#endif
