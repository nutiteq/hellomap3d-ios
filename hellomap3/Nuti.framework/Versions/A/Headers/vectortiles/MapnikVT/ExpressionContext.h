/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_EXPRESSIONCONTEXT_H_
#define _NUTI_MAPNIKVT_EXPRESSIONCONTEXT_H_

#include "Value.h"

#include <map>
#include <memory>

namespace Nuti { namespace MapnikVT {
	class Expression;
	class FeatureData;

	class ExpressionContext {
	public:
		using NutiParameterValueMap = std::map<std::string, Value>;

		ExpressionContext();

		void setZoom(int zoom);
		int getZoom() const { return _zoom; }
		float getScaleDenominator() const { return _scaleDenom; }

		void setFeatureData(std::shared_ptr<FeatureData> featureData) { _featureData = std::move(featureData); }
		const std::shared_ptr<FeatureData>& getFeatureDataPtr() const { return _featureData; }

		void setNutiParameterValueMap(NutiParameterValueMap paramValueMap) { _nutiParameterValueMap = std::move(paramValueMap); }
		const NutiParameterValueMap& getNutiParameterValueMap() const { return _nutiParameterValueMap; }

		Value getVariable(const std::string& name) const;

    private:
		int _zoom = 0;
		float _scaleDenom = 0;
        std::shared_ptr<FeatureData> _featureData;
		NutiParameterValueMap _nutiParameterValueMap;
	};
} }

#endif
