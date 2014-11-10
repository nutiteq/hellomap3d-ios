#ifndef STYLE_H_
#define STYLE_H_

#include "graphics/Color.h"

namespace Nuti {

/**
 * A base class for other Style objects.
 */
class Style {
public:
	virtual ~Style();

    /**
     * Returns the color of the vector element.
     * @return The color of the vector element.
     */
	const Color& getColor() const;

protected:
	Style(const Color& color);

	Color _color;

};

}

#endif
