#ifndef LINEDRAWDATA_H_
#define LINEDRAWDATA_H_

#include "drawdatas/VectorElementDrawData.h"
#include "styles/LineStyle.h"

#include <memory>
#include <vector>
#include <cglib/vec.h>

namespace Nuti {

class Bitmap;
class Line;
class LineStyle;
class MapPos;
class MapVec;
class Polygon;
class Projection;
class Tuple3D;

class LineDrawData : public VectorElementDrawData {
public:
	// Saves a little space compared to MapPos
	LineDrawData(const Line& line, const LineStyle& style, const Projection& projection);
	LineDrawData(const Polygon& polygon, const std::vector<MapPos>& internalPoses, const LineStyle& style, const Projection& projection);
    LineDrawData(const LineDrawData& lineDrawData);
	virtual ~LineDrawData();

	const std::shared_ptr<Bitmap> getBitmap() const;

	float getClickScale() const;

	const std::vector<std::vector<MapPos*> >& getCoords() const;

	const std::vector<std::vector<cglib::vec2<float> > >& getNormals() const;

	const std::vector<std::vector<cglib::vec2<float> > >& getTexCoords() const;

	const std::vector<std::vector<unsigned int> >& getIndices() const;

	void offsetHorizontally(double offset);

private:
	static const float LINE_ENDPOINT_TESSELATION_FACTOR;
	static const float LINE_JOINT_TESSELATION_FACTOR;

	static const int IDEAL_CLICK_WIDTH = 64;

	static const float CLICK_WIDTH_COEF;
    
	void init(const LineStyle& style);

	std::shared_ptr<Bitmap> _bitmap;

	float _clickScale;

	// Actual line coordinates
	std::vector<MapPos> _poses;

	// Origin point and normal for each vertex
	std::vector<std::vector<MapPos*> > _coords;
	std::vector<std::vector<cglib::vec2<float> > > _normals;
	std::vector<std::vector<cglib::vec2<float> > > _texCoords;

	std::vector<std::vector<unsigned int> > _indices;
};

}

#endif
