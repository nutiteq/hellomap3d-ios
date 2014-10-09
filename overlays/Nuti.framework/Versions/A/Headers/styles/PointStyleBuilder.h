#ifndef POINTSTYLEBUILDER_H_
#define POINTSTYLEBUILDER_H_

#include "styles/StyleBuilder.h"

#include <memory>

namespace Nuti {

class Bitmap;
class PointStyle;

/**
 * A builder class for PointStyle.
 */
class PointStyleBuilder : public StyleBuilder {
public:
    /**
     * Constructs a PointStyleBuilder object with all parameters set to defaults.
     */
	PointStyleBuilder();
	virtual ~PointStyleBuilder();

    /**
     * Returns the bitmap of the point.
     * @return The bitmap of the point.
     */
    std::shared_ptr<Bitmap> getBitmap() const;
    /**
     * Sets the bitmap that will be used for drawing the point. The default is "default_point.png".
     * @param bitmap The new bitmap for the point.
     */
	void setBitmap(const std::shared_ptr<Bitmap>& bitmap);
    
    /**
     * Returns the size of the point used for click detection.
     * @return The size of the point used for click detection.
     */
    float getClickSize() const;
    /**
     * Sets the size for the point that will be used for click detection.
     * Units are screen density independent pixels (DP or DIP). If set to -1 the click size will be
     * calculated automatically. The default is -1.
     * @param width The new point size in dp.
     */
	void setClickSize(float size);

    /**
     * Returns the size of the point.
     * @return The size of the point.
     */
    float getSize() const;
    /**
     * Sets the size for the point in screen density independent pixels (DP or DIP). The default is 20.
     * @param width The new point size in dp.
     */
	void setSize(float size);

    /**
     * Builds a new instance of the PointStyle object using previously set parameters.
     * @return A new PointStyle object.
     */
	std::shared_ptr<PointStyle> buildStyle();

protected:
	static std::shared_ptr<Bitmap> GetDefaultBitmap();

	static std::shared_ptr<Bitmap> _DefaultBitmap;

	std::shared_ptr<Bitmap> _bitmap;
    
    float _clickSize;

	float _size;
};

}

#endif
