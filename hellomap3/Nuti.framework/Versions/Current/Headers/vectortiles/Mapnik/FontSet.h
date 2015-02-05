/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_FONTSET_H_
#define _NUTI_MAPNIK_FONTSET_H_

#include <string>
#include <vector>

namespace Nuti { namespace Mapnik {
	class FontSet {
	public:
		explicit FontSet(const std::string& name) : _name(name) { }

		const std::string& getName() const { return _name; }

		const std::vector<std::string>& getFaceNames() const { return _faceNames; }

		void clearFaceNames() {
			_faceNames.clear();
		}
			
		void addFaceName(const std::string& faceName) {
			_faceNames.push_back(faceName);
		}

	private:
		const std::string _name;
		std::vector<std::string> _faceNames;
	};
} }

#endif
