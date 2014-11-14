#ifndef POLYGON3DDRAWDATA_H_
#define POLYGON3DDRAWDATA_H_

#include "core/MapBounds.h"
#include "drawdatas/VectorElementDrawData.h"

#include <memory>
#include <vector>

namespace Nuti {

class MapPos;
class Polygon3D;
class Polygon3DStyle;
class Projection;

class Polygon3DDrawData : public VectorElementDrawData {
public:
    // Saves a little space compared to MapPos
	class Vector3F {
	public:
		Vector3F(float x, float y, float z);
		Vector3F(const Tuple3D& mapPos);
		float getX() const;
		float getY() const;
        float getZ() const;
        
	private:
		float _x;
		float _y;
        float _z;
	};
    
	Polygon3DDrawData(const Polygon3D& polygon3D, const Polygon3DStyle& style, const Projection& projection);
    Polygon3DDrawData(const Polygon3DDrawData& drawData);
	virtual ~Polygon3DDrawData();

	const MapBounds& getBoundingBox() const;

	const std::vector<MapPos>& getCoords() const;

	const std::vector<Vector3F>& getNormals() const;

	void offsetHorizontally(double offset);

private:
	static const int MAX_INDICES_PER_ELEMENT = 3;

	MapBounds _boundingBox;

	std::vector<MapPos> _coords;
    
    std::vector<Vector3F> _normals;
    
};

}

#endif
