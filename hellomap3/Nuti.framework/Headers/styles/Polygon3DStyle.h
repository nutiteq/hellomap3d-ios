#ifndef POLYGON3DSTYLE_H_
#define POLYGON3DSTYLE_H_

#include "styles/Style.h"

#include <memory>

namespace Nuti {

/**
 * A style for 3d polygons. Contains attributes for configuring how the 3d polygon is drawn on the screen.
 */
class Polygon3DStyle: public Style {
public:
    /**
     * Constructs a Polygon3DStyle object from various parameters. Instantiating the object directly is
     * not recommended, Polygon3DStyleBuilder should be used instead.
     * @param color The color for the 3d polygon.
     */
	Polygon3DStyle(const Color& color);
	virtual ~Polygon3DStyle();
    
};

}

#endif
