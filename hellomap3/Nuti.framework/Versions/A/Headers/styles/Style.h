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
         * Returns the actual class name of this style. This is used
         * for dynamically creating Java and ObjC proxy classes, because Swig can't automatically
         * generate child proxy classes from a base class pointer.
         * @return The class name of this style.
         */
        const std::string& getClassName() const;

        /**
         * Returns the color of the vector element.
         * @return The color of the vector element.
         */
        const Color& getColor() const;
    
    protected:
        Style(const std::string& className, const Color& color);
    
        Color _color;

        std::string _className; // This is used by swig to generate correct proxy object
    };

}

#endif
