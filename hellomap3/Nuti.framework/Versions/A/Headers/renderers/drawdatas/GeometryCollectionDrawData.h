/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_GEOMETRYCOLLECTIONDRAWDATA_H_
#define _NUTI_GEOMETRYCOLLECTIONDRAWDATA_H_

#include "core/MapPos.h"
#include "renderers/drawdatas/VectorElementDrawData.h"

#include <memory>
#include <vector>

namespace Nuti {
    class Bitmap;
    class Geometry;
    class MultiGeometry;
    class GeometryCollection;
    class GeometryCollectionStyle;
    class Projection;

    class GeometryCollectionDrawData : public VectorElementDrawData {
    public:
        GeometryCollectionDrawData(const MultiGeometry& geometry, const GeometryCollectionStyle& style, const Projection& projection);
        virtual ~GeometryCollectionDrawData();

        const std::vector<std::shared_ptr<VectorElementDrawData> >& getDrawDatas() const;

        virtual void offsetHorizontally(double offset);

    private:
        void addDrawData(const Geometry& geometry, const GeometryCollectionStyle& style, const Projection& projection);

        std::vector<std::shared_ptr<VectorElementDrawData> > _drawDatas;
    };

}

#endif
