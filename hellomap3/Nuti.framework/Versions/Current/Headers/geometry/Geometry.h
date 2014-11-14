#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "core/MapPos.h"
#include "core/MapBounds.h"

namespace Nuti {

class Geometry {
public:
	virtual ~Geometry() {}
	
	virtual MapPos getCenterPos() const = 0;

	const MapBounds& getBounds() const {
		return _bounds;
	}

protected:
	Geometry() : _bounds() {}

	MapBounds _bounds;

};

}

#endif
