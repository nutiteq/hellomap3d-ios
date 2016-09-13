/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_LAYER_H_
#define _NUTI_MAPNIKVT_LAYER_H_

#include <string>
#include <vector>
#include <map>

namespace Nuti { namespace MapnikVT {
	class Layer {
	public:
		explicit Layer(std::string name, std::vector<std::string> styleNames) : _name(std::move(name)), _styleNames(std::move(styleNames)) { }
		virtual ~Layer() = default;

		const std::string& getName() const { return _name; }
		const std::vector<std::string>& getStyleNames() const { return _styleNames; }

	private:
		const std::string _name;
		const std::vector<std::string> _styleNames;
	};
} }

#endif
