/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_SYMBOLIZER_H_
#define _NUTI_MAPNIK_SYMBOLIZER_H_

#include <string>

namespace Nuti { namespace Mapnik {
	class Symbolizer {
	public:
		virtual ~Symbolizer() = default;

		virtual void setParameter(const std::string& name, const std::string& value) = 0;
	};
} }

#endif
