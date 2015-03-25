/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_GEOMETRY_H_
#define _NUTI_GEOMETRY_H_

#include "core/MapPos.h"
#include "core/MapBounds.h"

#include <string>

namespace Nuti {

    /**
     * A base class for all geometry types.
     */
    class Geometry {
    public:
        virtual ~Geometry() {}
        
        /**
         * Returns the actual class name of this geometry. This is used
         * for dynamically creating Java and ObjC proxy classes, because Swig can't automatically
         * generate child proxy classes from a base class pointer.
         * @return The class name of this layer.
         */
        const std::string& getClassName() const { return _className; }

        /**
         * Returns the center point of the geometry.
         * @return The center point of the geometry.
         */
        virtual MapPos getCenterPos() const = 0;
    
        /**
         * Returns the minimal bounds for the geometry.
         * @return The bounds for the geometry.
         */
        const MapBounds& getBounds() const {
            return _bounds;
        }
    
    protected:
        Geometry(const std::string& className) : _bounds(), _className(className) {}
    
        MapBounds _bounds;

    private:
        std::string _className; // This is used by swig to generate correct proxy object
    };
    
}

#endif
