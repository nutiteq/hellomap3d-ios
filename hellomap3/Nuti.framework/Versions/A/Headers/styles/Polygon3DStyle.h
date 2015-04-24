/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_POLYGON3DSTYLE_H_
#define _NUTI_POLYGON3DSTYLE_H_

#include "styles/Style.h"

#include <memory>

namespace Nuti {

    /**
     * A style for 3d polygons. Contains attributes for configuring how the 3d polygon is drawn on the screen.
     */
    class Polygon3DStyle: public Style {
    public:
        /**
         * Constructs a Polygon3DStyle object from various parameters. Instantiating the object directly is
         * not recommended, Polygon3DStyleBuilder should be used instead.
         * @param color The color for the 3d polygon.
         */
        Polygon3DStyle(const Color& color);
        virtual ~Polygon3DStyle();
    };
    
}

#endif
