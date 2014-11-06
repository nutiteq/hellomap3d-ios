#pragma once

#include "Expression.h"
#include "ConstExpression.h"
#include "ExpressionContext.h"

#include <vector>
#include <memory>

#include <boost/variant.hpp>
#include <boost/lexical_cast.hpp>

namespace Nuti {
	namespace Mapnik {
		namespace detail {
			template <typename V>
			struct BinderConverter {
				static V convert(const Value& val) {
					switch (val.which()) {
					case BOOL_VALUE:
						return static_cast<V>(boost::get<bool>(val));
					case LONG_VALUE:
						return static_cast<V>(boost::get<long long>(val));
					case DOUBLE_VALUE:
						return static_cast<V>(boost::get<double>(val));
					case STRING_VALUE:
						return boost::lexical_cast<V>(boost::get<std::string>(val));
					default:
						return V();
					}
				}
			};

			template <>
			struct BinderConverter<bool> {
				static bool convert(const Value& val) {
					switch (val.which()) {
					case BOOL_VALUE:
						return boost::get<bool>(val);
					case LONG_VALUE:
						return boost::get<long long>(val) != 0;
					case DOUBLE_VALUE:
						return boost::get<double>(val) != 0;
					case STRING_VALUE:
						return boost::lexical_cast<bool>(boost::get<std::string>(val));
					default:
						return false;
					}
				}
			};

			template <>
			struct BinderConverter<std::string> {
				static std::string convert(const Value& val) {
					switch (val.which()) {
					case BOOL_VALUE:
						return boost::lexical_cast<std::string>(boost::get<bool>(val));
					case LONG_VALUE:
						return boost::lexical_cast<std::string>(boost::get<long long>(val));
					case DOUBLE_VALUE:
						return boost::lexical_cast<std::string>(boost::get<double>(val));
					case STRING_VALUE:
						return boost::get<std::string>(val);
					default:
						return std::string();
					}
				}
			};

			struct BinderSetter : public boost::static_visitor<> {
				BinderSetter(const ExpressionContext& context) : _exprContext(context) { }

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
					*field = detail::BinderConverter<V>::convert(constExpr->getConstant());
				}
				else {
					_bindingMap.insert({ field, Binding<V>(field, expr, &detail::BinderConverter<V>::convert) });
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
					boost::apply_visitor(detail::BinderSetter(context), binding);
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
	}
}
