#ifndef POLYGON3DSTYLEBUILDER_H_
#define POLYGON3DSTYLEBUILDER_H_

#include "styles/StyleBuilder.h"

#include <memory>

namespace Nuti {

class Polygon3DStyle;

/**
 * A builder class for Polygon3DStyle.
 */
class Polygon3DStyleBuilder : public StyleBuilder {
public:
    /**
     * Constructs a Polygon3DStyleBuilder object with all parameters set to defaults.
     */
	Polygon3DStyleBuilder();
	virtual ~Polygon3DStyleBuilder();

    /**
     * Builds a new instance of the Polygon3DStyle object using previously set parameters.
     * @return A new Polygon3DStyle object.
     */
	std::shared_ptr<Polygon3DStyle> buildStyle();
    
};

}

#endif
