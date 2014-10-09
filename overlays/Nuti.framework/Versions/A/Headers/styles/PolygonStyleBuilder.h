#ifndef POLYGONSTYLEBUILDER_H_
#define POLYGONSTYLEBUILDER_H_

#include "styles/StyleBuilder.h"

#include <memory>

namespace Nuti {

class Bitmap;
class LineStyle;
class PolygonStyle;

/**
 * A builder class for PolygonStyle.
 */
class PolygonStyleBuilder : public StyleBuilder {
public:
    /**
     * Constructs a PolygonStyleBuilder object with all parameters set to defaults.
     */
	PolygonStyleBuilder();
	virtual ~PolygonStyleBuilder();

    /**
     * Returns the bitmap of the point.
     * @return The bitmap of the point.
     */
    //std::shared_ptr<Bitmap> getBitmap() const;
    /**
     * Sets the bitmap that will be used for drawing the polygon. The image will be repeated 
     * vertically and horizontally to cover the polygon. The default is "default_polygon.png"
     * @param bitmap The new bitmap for the polygon.
     */
	//void setBitmap(const std::shared_ptr<Bitmap>& bitmap);

    /**
     * Returns the line style of the edges of the polygon.
     * @return The line style of the edges of the polygon. May be null.
     */
    std::shared_ptr<LineStyle> getLineStyle() const;
    /**
     * Sets the line style that will be used to draw the edges of the polygon. If null is passed
     * no edges will be drawn. The default is null.
     * @param lineStyle The new style for the edges of the polygon.
     */
	void setLineStyle(const std::shared_ptr<LineStyle>& lineStyle);

    /**
     * Builds a new instance of the PolygonStyle object using previously set parameters.
     * @return A new PolygonStyle object.
     */
	std::shared_ptr<PolygonStyle> buildStyle();

protected:
	static std::shared_ptr<Bitmap> GetDefaultBitmap();

	static std::shared_ptr<Bitmap> _DefaultBitmap;

	std::shared_ptr<Bitmap> _bitmap;

	std::shared_ptr<LineStyle> _lineStyle;
};

}

#endif
