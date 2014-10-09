#ifndef POINTGEOMETRY_H_
#define POINTGEOMETRY_H_

#include "geometry/Geometry.h"
#include "core/MapPos.h"

namespace Nuti {

class PointGeometry : public Geometry {
public:
	PointGeometry(const MapPos& pos);
	virtual ~PointGeometry();

	const MapPos& getPos() const;

private:
	MapPos _pos;

};

}

#endif
