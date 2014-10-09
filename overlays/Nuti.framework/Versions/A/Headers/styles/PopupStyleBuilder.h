#ifndef POPUPSTYLEBUILDER_H_
#define POPUPSTYLEBUILDER_H_

#include "styles/BillboardStyleBuilder.h"

#include <memory>

namespace Nuti {

class PopupStyle;

/**
 * A builder class for PopupStyle.
 */
class PopupStyleBuilder : public BillboardStyleBuilder {
public:
    /**
     * Constructs a PopupStyleBuilder object with all parameters set to defaults.
     */
	PopupStyleBuilder();
	virtual ~PopupStyleBuilder();

    /**
     * Builds a new instance of the PopupStyle object using previously set parameters.
     * @return A new PopupStyle object.
     */
	std::shared_ptr<PopupStyle> buildStyle();

};

}

#endif
