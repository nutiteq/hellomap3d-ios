/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_PARAMETER_H_
#define _NUTI_MAPNIKVT_PARAMETER_H_

#include <memory>
#include <string>

namespace Nuti { namespace MapnikVT {
	class Parameter {
	public:
        explicit Parameter(std::string name, std::string value) : _name(std::move(name)), _value(std::move(value)) { }

		const std::string& getName() const { return _name; }
		const std::string& getValue() const { return _value; }

	private:
		std::string _name;
		std::string _value;
	};
} }

#endif
