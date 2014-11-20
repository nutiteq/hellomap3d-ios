#ifndef POLYGONGEOMETRY_H_
#define POLYGONGEOMETRY_H_

#include "geometry/Geometry.h"

#include <vector>

namespace Nuti {

/**
 * Polygon geometry defined by an outer ring and optional multiple inner rings (holes).
 */
class PolygonGeometry : public Geometry {
public:
	/**
	 * Constructs a PolygonGeometry objects from an outer ring.
	 * @param poses The list of map positions defining the outer ring.
	 */
	PolygonGeometry(const std::vector<MapPos>& poses);
	/**
	 * Constructs a PolygonGeometry objects from an outer ring and list of inner rings (holes).
	 * @param poses The list of map positions defining the outer ring.
	 * @param holes The list of map position lists defining the inner rings.
	 */
	PolygonGeometry(const std::vector<MapPos>& poses, const std::vector<std::vector<MapPos> >& holes);
	virtual ~PolygonGeometry();
	
	virtual MapPos getCenterPos() const;

	/**
	 * Returns the list of map positions defining the outer ring of the polygon.
	 * @returns The list of map positions defining the outer ring of the polygon.
	 */
	const std::vector<MapPos>& getPoses() const;

	/**
	 * Returns the list of map position lists defining the inner rings of the polygon (holes).
	 * @returns The list of map position lists defining the inner rings of the polygon (holes).
	 */
	const std::vector<std::vector<MapPos> >& getHoles() const;

private:
	std::vector<MapPos> _poses;

	std::vector<std::vector<MapPos> > _holes;

};

}

#endif
