/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_EXPRESSIONCONTEXT_H_
#define _NUTI_MAPNIK_EXPRESSIONCONTEXT_H_

#include "Value.h"
#include "Expression.h"
#include "ScaleUtils.h"

#include <map>
#include <memory>

#include <boost/lexical_cast.hpp>

namespace Nuti { namespace Mapnik {
	class ExpressionContext {
	public:
		enum class GeometryType {
			NULL_GEOMETRY = 0, POINT_GEOMETRY = 1, LINE_GEOMETRY = 2, POLYGON_GEOMETRY = 3
		};

		using VariableMap = std::map<std::string, Value>;
		using NutiParameterValueMap = std::map<std::string, Value>;

		ExpressionContext() = default;

		void setZoom(int zoom) { _zoom = zoom; }
		int getZoom() const { return _zoom; }

		void setGeometryType(GeometryType geometryType) { _geometryType = geometryType; }
		GeometryType getGeometryType() const { return _geometryType; }

		void setVariableMap(const std::shared_ptr<VariableMap>& variableMap) { _variableMap = variableMap; }
		const std::shared_ptr<VariableMap>& getVariableMap() const { return _variableMap; }

		void setNutiParameterValueMap(const std::shared_ptr<NutiParameterValueMap>& paramValueMap) { _nutiParameterValueMap = paramValueMap; }
		const std::shared_ptr<NutiParameterValueMap>& getNutiParameterValueMap() const { return _nutiParameterValueMap; }

		float getScaleDenominator() const {
			return zoom2ScaleDenominator(static_cast<float>(_zoom));
		}

		bool evaluateBoolean(const Expression& expr) const {
			Value result = expr.evaluate(*this);
			switch (result.getType()) {
			case Value::Type::BOOL_VALUE:
				return result.getBool();
			case Value::Type::LONG_VALUE:
				return result.getLong() != 0;
			case Value::Type::DOUBLE_VALUE:
				return result.getDouble() != 0;
			case Value::Type::STRING_VALUE:
				return boost::lexical_cast<bool>(result.getString());
			default:
				return false;
			}
		}

		long long evaluateLong(const Expression& expr) const {
			Value result = expr.evaluate(*this);
			switch (result.getType()) {
			case Value::Type::BOOL_VALUE:
				return static_cast<long long>(result.getBool());
			case Value::Type::LONG_VALUE:
				return result.getLong();
			case Value::Type::DOUBLE_VALUE:
				return static_cast<long long>(result.getDouble());
			case Value::Type::STRING_VALUE:
				return boost::lexical_cast<long long>(result.getString());
			default:
				return 0;
			}
		}

		double evaluateDouble(const Expression& expr) const {
			Value result = expr.evaluate(*this);
			switch (result.getType()) {
			case Value::Type::BOOL_VALUE:
				return static_cast<double>(result.getBool());
			case Value::Type::LONG_VALUE:
				return static_cast<double>(result.getLong());
			case Value::Type::DOUBLE_VALUE:
				return result.getDouble();
			case Value::Type::STRING_VALUE:
				return boost::lexical_cast<double>(result.getString());
			default:
				return 0.0;
			}
		}

		std::string evaluateString(const Expression& expr) const {
			Value result = expr.evaluate(*this);
			switch (result.getType()) {
			case Value::Type::NULL_VALUE:
				return std::string();
			case Value::Type::STRING_VALUE:
				return result.getString();
			default:
				return boost::lexical_cast<std::string>(result);
			}
		}

		Value getVariable(const std::string& name) const {
			if (_variableMap) {
				VariableMap::const_iterator it = _variableMap->find(name);
				if (it != _variableMap->end()) {
					return it->second;
				}
			}
			if (name.compare(0, 6, "nuti::") == 0) {
				NutiParameterValueMap::const_iterator it = _nutiParameterValueMap->find(name.substr(6));
				if (it != _nutiParameterValueMap->end()) {
					return it->second;
				}
			}
			if (name.compare("mapnik::geometry_type") == 0) {
				return Value(static_cast<long long>(getGeometryType()));
			}
			return Value();
		}

	private:
		int _zoom = 0;
		GeometryType _geometryType = GeometryType::NULL_GEOMETRY;
		std::shared_ptr<VariableMap> _variableMap;
		std::shared_ptr<NutiParameterValueMap> _nutiParameterValueMap;
	};
} }

#endif
