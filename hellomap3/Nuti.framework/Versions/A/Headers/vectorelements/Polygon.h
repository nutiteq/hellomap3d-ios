#ifndef POLYGON_H_
#define POLYGON_H_

#include "vectorelements/VectorElement.h"

#include <vector>

namespace Nuti {

class PolygonDrawData;
class PolygonGeometry;
class PolygonStyle;
class MapPos;

/**
 * A geometric polygon that can be displayed on the map.
 * Polygons can be concave and have multiple overlapping holes.
 */
class Polygon : public VectorElement {
public:
    /**
     * Constructs a Polygon object from a geometry object and a style.
     * @param geometry The geometry object that defines the location and holes of this polygon.
     * @param style The style that defines what this polygon looks like.
     */
	Polygon(const std::shared_ptr<PolygonGeometry>& geometry, const std::shared_ptr<PolygonStyle>& style);
    /**
     * Constructs a Polygon object from a vector of map positions and a style.
     * @param poses The vector of map positions that defines the location of this polygon.
     * @param style The style that defines what this polygon looks like.
     */
    Polygon(const std::vector<MapPos>& poses, const std::shared_ptr<PolygonStyle>& style);
    /**
     * Constructs a Polygon object from a vector of map positions, a vector of holes and a style.
     * @param poses The vector of map positions that defines the location of this polygon.
     * @param holes The vector of holes that defines the locations of holes of this polygon.
     * @param style The style that defines what this polygon looks like.
     */
	Polygon(const std::vector<MapPos>& poses, const std::vector<std::vector<MapPos> >& holes,
            const std::shared_ptr<PolygonStyle>& style);
	virtual ~Polygon();

	std::shared_ptr<PolygonGeometry> getGeometry() const;
    /**
     * Sets the location for this polygon.
     * @param geometry The new geometry object that defines the location and holes of this polygon.
     */
	void setGeometry(const std::shared_ptr<PolygonGeometry>& geometry);
    /**
     * Sets the location for this polygon.
     * @param poses The new vector of map positions that define the location of this polygon.
     */
    void setPoses(const std::vector<MapPos>& poses);
    /**
     * Sets the location and holes for this polygon.
     * @param poses The new vector of map positions that defines the location of this polygon.
     * @param holes The new vector of holes that defines the locations of holes of this polygon.
     */
	void setPoses(const std::vector<MapPos>& poses, const std::vector<std::vector<MapPos> >& holes);

    /**
     * Returns the style of this polygon.
     * @return The style that defines what this polygon looks like.
     */
	std::shared_ptr<PolygonStyle> getStyle() const;
    /**
     * Sets the style for this polygon.
     * @param style The new style that defines what this polygon looks like.
     */
	void setStyle(const std::shared_ptr<PolygonStyle>& style);

protected:
    friend class PolygonRenderer;
    friend class VectorLayer;
    
    std::shared_ptr<PolygonDrawData> getDrawData() const;
    void setDrawData(const std::shared_ptr<PolygonDrawData>& drawData);
    
private:
    std::shared_ptr<PolygonDrawData> _drawData;
    
	std::shared_ptr<PolygonStyle> _style;

};

}

#endif
