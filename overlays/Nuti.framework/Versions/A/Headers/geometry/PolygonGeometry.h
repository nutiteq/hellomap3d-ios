#ifndef POLYGONGEOMETRY_H_
#define POLYGONGEOMETRY_H_

#include "geometry/Geometry.h"

#include <vector>

namespace Nuti {

class MapPos;

class PolygonGeometry : public Geometry {
public:
	PolygonGeometry(const std::vector<MapPos>& poses);
	PolygonGeometry(const std::vector<MapPos>& poses, const std::vector<std::vector<MapPos> >& holes);
	virtual ~PolygonGeometry();

	const std::vector<MapPos>& getPoses() const;

	const std::vector<std::vector<MapPos> >& getHoles() const;

private:
	std::vector<MapPos> _poses;

	std::vector<std::vector<MapPos> > _holes;

};

}

#endif
