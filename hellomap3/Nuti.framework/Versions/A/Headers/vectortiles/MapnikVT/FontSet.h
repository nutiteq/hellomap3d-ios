/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_FONTSET_H_
#define _NUTI_MAPNIKVT_FONTSET_H_

#include <string>
#include <vector>

namespace Nuti { namespace MapnikVT {
	class FontSet {
	public:
		explicit FontSet(std::string name, std::vector<std::string> faceNames) : _name(std::move(name)), _faceNames(std::move(faceNames)) { }

		const std::string& getName() const { return _name; }
		const std::vector<std::string>& getFaceNames() const { return _faceNames; }

	private:
		const std::string _name;
		const std::vector<std::string> _faceNames;
	};
} }

#endif
