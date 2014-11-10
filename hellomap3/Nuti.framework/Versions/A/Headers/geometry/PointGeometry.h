#ifndef POINTGEOMETRY_H_
#define POINTGEOMETRY_H_

#include "geometry/Geometry.h"

namespace Nuti {

class PointGeometry : public Geometry {
public:
	PointGeometry(const MapPos& pos);
	virtual ~PointGeometry();

	virtual MapPos getCenterPos() const;
	const MapPos& getPos() const;

private:
	MapPos _pos;

};

}

#endif
