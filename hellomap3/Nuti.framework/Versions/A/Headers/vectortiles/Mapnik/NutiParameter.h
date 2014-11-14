/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_NUTIPARAMETER_H_
#define _NUTI_MAPNIK_NUTIPARAMETER_H_

#include "Value.h"

#include <memory>
#include <string>
#include <map>

namespace Nuti { namespace Mapnik {
	class NutiParameter {
	public:
		NutiParameter(const std::string& name, const Value& defaultValue, const std::map<std::string, Value>& enumMap) : _name(name), _defaultValue(defaultValue), _enumMap(enumMap) { }

		const std::string& getName() const { return _name; }
		const Value& getDefaultValue() const { return _defaultValue; }
		const std::map<std::string, Value>& getEnumMap() const { return _enumMap; }

	private:
		std::string _name;
		Value _defaultValue;
		std::map<std::string, Value> _enumMap;
	};
} }

#endif
