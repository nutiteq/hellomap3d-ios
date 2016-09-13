/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_NUTIPARAMETER_H_
#define _NUTI_MAPNIKVT_NUTIPARAMETER_H_

#include "Value.h"

#include <memory>
#include <string>
#include <map>

namespace Nuti { namespace MapnikVT {
	class NutiParameter {
	public:
        explicit NutiParameter(std::string name, Value defaultValue, std::map<std::string, Value> enumMap) : _name(std::move(name)), _defaultValue(std::move(defaultValue)), _enumMap(std::move(enumMap)) { }

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
