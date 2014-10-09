#ifndef VECTORELEMENTCLICKINFO_H_
#define VECTORELEMENTCLICKINFO_H_

#include "core/MapPos.h"

#include <memory>

namespace Nuti {

class VectorElement;

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
     * @param distance The distance from the vector element to the camera in the internal coordiante system.
     * @param order The draw order of this element relative to others.
     * @param vectorElement The vector element on which the click was performed.
     */
	VectorElementClickInfo(const MapPos& clickPos, const MapPos& elementClickPos, double distance, unsigned int order, const std::shared_ptr<VectorElement>& vectorElement);
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

private:
	MapPos _clickPos;
    MapPos _elementClickPos;

	double _distance;

	unsigned int _order;

	std::shared_ptr<VectorElement> _vectorElement;
};

}

#endif
