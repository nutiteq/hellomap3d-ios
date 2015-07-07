/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MULTIPOINTGEOMETRY_H_
#define _NUTI_MULTIPOINTGEOMETRY_H_

#include "geometry/MultiGeometry.h"
#include "geometry/PointGeometry.h"

namespace Nuti {

    /**
     * A multipoint container.
     */
    class MultiPointGeometry : public MultiGeometry {
    public:
        /**
         * Constructs a MultiPointGeometry from the vector of points.
         */
        MultiPointGeometry(const std::vector<std::shared_ptr<PointGeometry> >& geometries);
        virtual ~MultiPointGeometry();

        /**
         * Returns the point geometry at the specified index. Index must be between 0 and getGeometryCount (exclusive)
         * @return The point geometry at specified index.
         */
        std::shared_ptr<PointGeometry> getGeometry(int index) const;
    };

}

#endif
