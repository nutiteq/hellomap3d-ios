/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VECTORELEMENTCLICKINFO_H_
#define _NUTI_VECTORELEMENTCLICKINFO_H_

#include "components/DirectorPtr.h"
#include "core/MapPos.h"
#include "vectorelements/VectorElement.h"

#include <memory>

namespace Nuti {
    class Layer;
    
    /**
     * A container class that provies information about a click performed on
     * a vector element.
     */
    class VectorElementClickInfo {
    public:
        /**
         * Constructs an empty VectorElementClickInfo object.
         */
        VectorElementClickInfo();
        /**
         * Constructs a VectorElementClickInfo object from a click position, distance, draw order and a vector element.
         * @param clickPos The click position in the coordinate system of the base projection.
         * @param elementClickPos The click position in the coordinate system of the base projection that corresponds to element point.
         * @param distance The distance from the vector element to the camera in the internal coordiante system.
         * @param order The draw order of this element relative to others.
         * @param vectorElement The vector element on which the click was performed.
         * @param layer The layer of the vector element on which the click was performed.
         */
        VectorElementClickInfo(const MapPos& clickPos, const MapPos& elementClickPos, double distance, unsigned int order, const std::shared_ptr<VectorElement>& vectorElement, const std::shared_ptr<Layer>& vectorLayer);
        virtual ~VectorElementClickInfo();
    
        /**
         * Returns the click position.
         * @return The click position in the coordinate system of the base projection.
         */
        const MapPos& getClickPos() const;
        
        /**
         * Returns the position on the clicked element, that is close to the click position.
         * For points it will always be the center position, for lines it will be the closest point
         * on the line, for billboards it will be the anchor point and for polygons it's equal to
         * getClickPos().
         * @return The element click position in the coordinate system of the base projection.
         */
        const MapPos& getElementClickPos() const;
    
        /**
         * Returns the distance from the vector element to the camera.
         * @return The distance from the vector element to the camera in the internal coordiante system.
         */
        double getDistance() const;
    
        /**
         * Returns the relative draw order of the vector element.
         * @return The draw order of this vector element relative to others vector elements,
         *         which where also clicked.
         */
        unsigned int getOrder() const;
        
        /**
         * Returns the clicked vector element.
         * @return The vector element on which the click was performed.
         */
        std::shared_ptr<VectorElement> getVectorElement() const;
        /**
         * Returns the layer of the clicked vector element.
         * @return The layer of the vector element on which the click was performed.
         */
        std::shared_ptr<Layer> getLayer() const;
    
    private:
        MapPos _clickPos;
        MapPos _elementClickPos;
    
        double _distance;
    
        unsigned int _order;
    
        DirectorPtr<VectorElement> _vectorElement;
        std::shared_ptr<Layer> _layer;
    };
    
}

#endif
