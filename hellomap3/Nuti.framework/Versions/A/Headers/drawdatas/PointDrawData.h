#ifndef POINTDRAWDATA_H_
#define POINTDRAWDATA_H_

#include "core/MapPos.h"
#include "drawdatas/VectorElementDrawData.h"
#include "styles/PointStyle.h"

#include <memory>

namespace Nuti {

class Bitmap;
class Point;
class PointStyle;
class Projection;

class PointDrawData : public VectorElementDrawData {
public:
	PointDrawData(const Point& point, const PointStyle& style, const Projection& projection);
	virtual ~PointDrawData();

	const std::shared_ptr<Bitmap> getBitmap() const;

	float getClickScale() const;

	const MapPos& getPos() const;

	float getSize() const;

	void offsetHorizontally(double offset);

private:
	static const int IDEAL_CLICK_SIZE = 64;

	static const float CLICK_SIZE_COEF;

	std::shared_ptr<Bitmap> _bitmap;

	float _clickScale;

	MapPos _pos;

	float _size;
};

}

#endif
