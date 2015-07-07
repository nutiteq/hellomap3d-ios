/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MULTIPOLYGONGEOMETRY_H_
#define _NUTI_MULTIPOLYGONGEOMETRY_H_

#include "geometry/MultiGeometry.h"
#include "geometry/PolygonGeometry.h"

namespace Nuti {
    
    /**
     * A multipolygon container.
     */
    class MultiPolygonGeometry : public MultiGeometry {
    public:
        /**
         * Constructs a MultiPolygonGeometry from the vector of polygons.
         */
        MultiPolygonGeometry(const std::vector<std::shared_ptr<PolygonGeometry> >& geometries);
        virtual ~MultiPolygonGeometry();
        
        /**
         * Returns the polygon geometry at the specified index. Index must be between 0 and getGeometryCount (exclusive)
         * @return The polygon geometry at specified index.
         */
        std::shared_ptr<PolygonGeometry> getGeometry(int index) const;
    };
    
}

#endif
