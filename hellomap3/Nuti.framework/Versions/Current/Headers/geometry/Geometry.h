#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "core/MapPos.h"
#include "core/MapBounds.h"

namespace Nuti {

/**
 * A base class for all geometry types.
 */
class Geometry {
public:
	virtual ~Geometry() {}
	
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
	Geometry() : _bounds() {}

	MapBounds _bounds;

};

}

#endif
