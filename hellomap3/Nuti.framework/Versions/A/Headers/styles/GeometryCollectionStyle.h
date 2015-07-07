/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_GEOMETRYCOLLECTIONSTYLE_H_
#define _NUTI_GEOMETRYCOLLECTIONSTYLE_H_

#include "styles/Style.h"

#include <memory>

namespace Nuti {
    class PointStyle;
    class LineStyle;
    class PolygonStyle;
    
    /**
     * A style for geometry collections. Contains styles for points, lines, polygons.
     */
    class GeometryCollectionStyle : public Style {
    public:
        GeometryCollectionStyle(const std::shared_ptr<PointStyle>& pointStyle, const std::shared_ptr<LineStyle>& lineStyle, const std::shared_ptr<PolygonStyle>& polygonStyle);
        virtual ~GeometryCollectionStyle();
        
        /**
         * Returns the point style.
         * @return The point style.
         */
        std::shared_ptr<PointStyle> getPointStyle() const;
        /**
         * Returns the line style.
         * @return The line style.
         */
        std::shared_ptr<LineStyle> getLineStyle() const;
        /**
         * Returns the polygon style.
         * @return The polygon style.
         */
        std::shared_ptr<PolygonStyle> getPolygonStyle() const;
        
    protected:
        std::shared_ptr<PointStyle> _pointStyle;
        std::shared_ptr<LineStyle> _lineStyle;
        std::shared_ptr<PolygonStyle> _polygonStyle;
    };
    
}

#endif
