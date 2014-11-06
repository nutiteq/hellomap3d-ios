#pragma once

#include "Value.h"
#include "Expression.h"
#include "ScaleUtils.h"

#include <map>
#include <memory>

#include <boost/lexical_cast.hpp>

namespace Nuti {
	namespace Mapnik {
		enum {
			NULL_GEOMETRY = 0, POINT_GEOMETRY = 1, LINE_GEOMETRY = 2, POLYGON_GEOMETRY = 3
		};

		class ExpressionContext {
		public:
			using VariableMap = std::map<std::string, Value>;

			ExpressionContext() = default;

			void setZoom(int zoom) { _zoom = zoom; }
			int getZoom() const { return _zoom; }

			void setGeometryType(int geometryType) { _geometryType = geometryType; }
			int getGeometryType() const { return _geometryType; }

			void setVariableMap(const std::shared_ptr<VariableMap>& variableMap) { _variableMap = variableMap; }
			const std::shared_ptr<VariableMap>& getVariableMap() const { return _variableMap; }

			float getScaleDenominator() const {
				return zoom2ScaleDenominator(static_cast<float>(_zoom));
			}

			bool evaluateBoolean(const Expression& expr) const {
				Value result = expr.evaluate(*this);
				switch (result.which()) {
				case BOOL_VALUE:
					return boost::get<bool>(result);
				case LONG_VALUE:
					return boost::get<long long>(result) != 0;
				case DOUBLE_VALUE:
					return boost::get<double>(result) != 0;
				default:
					return false;
				}
			}

			long long evaluateLong(const Expression& expr) const {
				Value result = expr.evaluate(*this);
				switch (result.which()) {
				case NULL_VALUE:
					return 0;
				case BOOL_VALUE:
					return static_cast<long long>(boost::get<bool>(result));
				case LONG_VALUE:
					return boost::get<long long>(result);
				case DOUBLE_VALUE:
					return static_cast<long long>(boost::get<double>(result));
				default:
					return boost::lexical_cast<long long>(result);
				}
			}

			double evaluateDouble(const Expression& expr) const {
				Value result = expr.evaluate(*this);
				switch (result.which()) {
				case NULL_VALUE:
					return 0;
				case BOOL_VALUE:
					return static_cast<double>(boost::get<bool>(result));
				case LONG_VALUE:
					return static_cast<double>(boost::get<long long>(result));
				case DOUBLE_VALUE:
					return boost::get<double>(result);
				default:
					return boost::lexical_cast<double>(result);
				}
			}

			std::string evaluateString(const Expression& expr) const {
				Value result = expr.evaluate(*this);
				switch (result.which()) {
				case NULL_VALUE:
					return std::string();
				case STRING_VALUE:
					return boost::get<std::string>(result);
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
				if (name == "mapnik::geometry_type") {
					return Value(static_cast<long long>(getGeometryType()));
				}
				return Value();
			}

		private:
			int _zoom = 0;
			int _geometryType = NULL_GEOMETRY;
			std::shared_ptr<VariableMap> _variableMap;
		};
	}
}
