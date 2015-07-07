/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_STYLE_H_
#define _NUTI_STYLE_H_

#include "graphics/Color.h"

namespace Nuti {

    /**
     * A base class for other Style objects.
     */
    class Style {
    public:
        virtual ~Style();
    
        /**
         * Returns the color of the vector element.
         * @return The color of the vector element.
         */
        const Color& getColor() const;
    
    protected:
        Style(const Color& color);
    
        Color _color;
    };

}

#endif
