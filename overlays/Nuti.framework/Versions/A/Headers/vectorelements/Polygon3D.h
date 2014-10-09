#ifndef POLYGON3D_H_
#define POLYGON3D_H_

#include "vectorelements/VectorElement.h"

#include <vector>

namespace Nuti {

class Polygon3DDrawData;
class Polygon3DStyle;
class PolygonGeometry;
class MapPos;

/**
 * A geometric 3d polygon that can be displayed on the map.
 * 3d polygons can be concave and have multiple overlapping holes.
 */
class Polygon3D : public VectorElement {
public:
    /**
     * Constructs a Polygon3D object from a geometry object and a style.
     * @param geometry The geometry object that defines the location and holes of this 3d polygon.
     * @param style The style that defines what this 3d polygon looks like.
     * @param height The height of this 3d polygon in meters.
     */
	Polygon3D(const std::shared_ptr<PolygonGeometry>& geometry, const std::shared_ptr<Polygon3DStyle>& style, float height);
    /**
     * Constructs a Polygon3D object from a vector of map positions and a style.
     * @param poses The vector of map positions that defines the location of this 3d polygon.
     * @param style The style that defines what this 3d polygon looks like.
     * @param height The height of this 3d polygon in meters.
     */
    Polygon3D(const std::vector<MapPos>& poses, const std::shared_ptr<Polygon3DStyle>& style, float height);
    /**
     * Constructs a Polygon3D object from a vector of map positions, a vector of holes and a style.
     * @param poses The vector of map positions that defines the location of this 3d polygon.
     * @param holes The vector of holes that defines the locations of holes of this 3d polygon.
     * @param style The style that defines what this 3d polygon looks like.
     * @param height The height of this 3d polygon in meters.
     */
	Polygon3D(const std::vector<MapPos>& poses, const std::vector<std::vector<MapPos> >& holes,
            const std::shared_ptr<Polygon3DStyle>& style, float height);
	virtual ~Polygon3D();

	std::shared_ptr<PolygonGeometry> getGeometry() const;
    /**
     * Sets the location for this 3d polygon.
     * @param geometry The new geometry object that defines the location and holes of this 3d polygon.
     */
	void setGeometry(const std::shared_ptr<PolygonGeometry>& geometry);
    /**
     * Sets the location for this 3d polygon.
     * @param poses The new vector of map positions that define the location of this 3d polygon.
     */
    void setPoses(const std::vector<MapPos>& poses);
    /**
     * Sets the location and holes for this 3d polygon.
     * @param poses The new vector of map positions that defines the location of this 3d polygon.
     * @param holes The new vector of holes that defines the locations of holes of this 3d polygon.
     */
	void setPoses(const std::vector<MapPos>& poses, const std::vector<std::vector<MapPos> >& holes);
    
    /**
     * Returns the height of this 3d polygon.
     * @return The height of this 3d polygon in meters.
     */
	float getHeight() const;
    /**
     * Sets the height for this 3d polygon.
     * @param style The new height for this 3d polygon in meters.
     */
	void setHeight(float height);

    /**
     * Returns the style of this 3d polygon.
     * @return The style that defines what this 3d polygon looks like.
     */
	std::shared_ptr<Polygon3DStyle> getStyle() const;
    /**
     * Sets the style for this 3d polygon.
     * @param style The new style that defines what this 3d polygon looks like.
     */
	void setStyle(const std::shared_ptr<Polygon3DStyle>& style);

protected:
    friend class Polygon3DRenderer;
    friend class VectorLayer;
    
    std::shared_ptr<Polygon3DDrawData> getDrawData() const;
    void setDrawData(const std::shared_ptr<Polygon3DDrawData>& drawData);
    
private:
    std::shared_ptr<Polygon3DDrawData> _drawData;
    
    float _height;
    
	std::shared_ptr<Polygon3DStyle> _style;

};

}

#endif
