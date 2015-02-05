/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_GEOMETRYSYMBOLIZER_H_
#define _NUTI_MAPNIKVT_GEOMETRYSYMBOLIZER_H_

#include "TileSymbolizer.h"

#include <boost/optional.hpp>

namespace Nuti {
	namespace MapnikVT {
		class GeometrySymbolizer : public TileSymbolizer {
		public:
			GeometrySymbolizer(const std::shared_ptr<Mapnik::Logger>& logger, const std::shared_ptr<Mapnik::Map>& map) : TileSymbolizer(logger, map) { }

			virtual void setParameter(const std::string& name, const std::string& value) override;

		protected:
			static boost::optional<cglib::mat3x3<float>> convertOptionalTransform(const Mapnik::Value& val);

			boost::optional<cglib::mat3x3<float>> _geometryTransform;
		};
	}
}

#endif
