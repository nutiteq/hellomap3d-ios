/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_EXPRESSIONCONTEXT_H_
#define _NUTI_MAPNIK_EXPRESSIONCONTEXT_H_

#include "Value.h"

#include <map>
#include <memory>

namespace Nuti { namespace Mapnik {
	class Expression;

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

		bool evaluateBoolean(const Expression& expr) const;
		long long evaluateLong(const Expression& expr) const;
		double evaluateDouble(const Expression& expr) const;
		std::string evaluateString(const Expression& expr) const;

		float getScaleDenominator() const;
		
		Value getVariable(const std::string& name) const;

	private:
		int _zoom = 0;
		GeometryType _geometryType = GeometryType::NULL_GEOMETRY;
		std::shared_ptr<VariableMap> _variableMap;
		std::shared_ptr<NutiParameterValueMap> _nutiParameterValueMap;
	};
} }

#endif
