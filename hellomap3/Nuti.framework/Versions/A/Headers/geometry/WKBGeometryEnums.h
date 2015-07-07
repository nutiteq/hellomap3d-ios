/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_WKBGEOMETRYENUMS_H_
#define _NUTI_WKBGEOMETRYENUMS_H_

namespace Nuti {
    
    enum wkbGeometryType {
        wkbPoint = 1,
        wkbLineString = 2,
        wkbPolygon = 3,
        wkbMultiPoint = 4,
        wkbMultiLineString = 5,
        wkbMultiPolygon = 6,
        wkbGeometryCollection = 7,

        wkbZMask = 0x1000,
        wkbMMask = 0x2000
    };

    enum wkbBigEndian {
        wkbXDR = 0,             // Big Endian
        wkbNDR = 1           // Little Endian
    };

}

#endif
