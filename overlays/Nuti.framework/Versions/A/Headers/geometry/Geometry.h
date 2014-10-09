#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "core/MapBounds.h"

namespace Nuti {

class Geometry {
public:
	virtual ~Geometry() {}

	const MapBounds& getBounds() const {
		return _bounds;
	}

protected:
	Geometry() : _bounds() {}

	MapBounds _bounds;

};

}

#endif
