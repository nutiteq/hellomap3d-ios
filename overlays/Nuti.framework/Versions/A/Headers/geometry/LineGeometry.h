#ifndef LINEGEOMETRY_H_
#define LINEGEOMETRY_H_

#include "geometry/Geometry.h"

#include <vector>

namespace Nuti {

class MapPos;

class LineGeometry : public Geometry {
public:
	LineGeometry(const std::vector<MapPos>& poses);
	virtual ~LineGeometry();

	const std::vector<MapPos>& getPoses() const;

private:
	std::vector<MapPos> _poses;

};

}

#endif
