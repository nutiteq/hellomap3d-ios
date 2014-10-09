#ifndef POPUPSTYLE_H_
#define POPUPSTYLE_H_

#include "styles/BillboardStyle.h"

#include <memory>

namespace Nuti {

class Bitmap;

/**
 * A style for popups. Contains attributes for configuring how the popup is drawn on the screen.
 */
class PopupStyle: public BillboardStyle {
public:
    /**
     * Constructs a PopupStyle object from various parameters. Instantiating the object directly is
     * not recommended, PopupStyleBuilder should be used instead.
     * @param color The color for the popup.
     * @param attachAnchorPointX The horizontal attaching anchor point for the popup.
     * @param attachAnchorPointY The vertical attaching anchor point for the popup.
     * @param causesOverlap The causes overlap flag for the popup.
     * @param hideIfOverlapped The hide if overlapped flag for the popup.
     * @param horizontalOffset The horizontal offset for the popup.
     * @param verticalOffset The vertical offset for the popup.
     * @param placementPriority The placement priority for the popup.
     * @param scaleWithDpi The scale with DPI flag for the label.
     */
	PopupStyle(const Color& color,
               float attachAnchorPointX,
               float attachAnchorPointY,
               bool causesOverlap,
               bool hideIfOverlapped,
               float horizontalOffset,
               float verticalOffset,
               int placementPriority,
               bool scaleWithDPI);
	virtual ~PopupStyle();

};

}

#endif
