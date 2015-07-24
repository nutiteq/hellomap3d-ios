/*
 * Copyright 2014 Nutiteq Llc.All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https ://www.nutiteq.com/license/
 */

#ifndef _NUTI_WKTGEOMETRYREADER_H_
#define _NUTI_WKTGEOMETRYREADER_H_

#ifdef _NUTI_WKBT_SUPPORT

#include <memory>
#include <string>

namespace Nuti {
    class Geometry;

    /**
     * A reader for Well Known Text representation of the geometry.
     */
    class WKTGeometryReader {
    public:
        /**
         * Constructs a WKTGeometryReader object.
         */
        WKTGeometryReader();

        /**
         * Reads geometry from the specified WKT string.
         * @param wkt The WKT string to read. For example, "POINT(1,1)"
         * @return The geometry read from the string. Null if reading failed.
         */
        std::shared_ptr<Geometry> readGeometry(const std::string& wkt) const;
    };

}

#endif

#endif
