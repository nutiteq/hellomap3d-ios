#ifndef STYLEBUILDER_H_
#define STYLEBUILDER_H_

#include "graphics/Color.h"

#include <mutex>

namespace Nuti {

/**
 * A base class for other StyleBuilder subclasses.
 */
class StyleBuilder {
public:
    /**
     * Copy constructs style builder from another style builder.
     * @param styleBuilder The other style builder.
     */
    StyleBuilder(const StyleBuilder& styleBuilder);
    virtual ~StyleBuilder();
    
    /**
	 * Copies the other style builder's parameters to this one.
	 * @param styleBuilder The other style builder.
	 * @return This style builder.
	 */
    StyleBuilder& operator=(const StyleBuilder& styleBuilder);
    
    /**
    * Returns the color of the vector element.
    * @return The color of the vector element.
    */
	const Color& getColor() const;
    /**
     * Sets the color for the vector element. Coloring works by multiplying the bitmap
     * of the vector element with the specified color. If the color is set to white, the resulting bitmap
     * will look exactly like the original. The default is white.
     * @param color The new color for the vector element.
     */
	void setColor(const Color& color);

protected:
	StyleBuilder();
    
	Color _color;
    
    mutable std::mutex _mutex;

};

}

#endif
