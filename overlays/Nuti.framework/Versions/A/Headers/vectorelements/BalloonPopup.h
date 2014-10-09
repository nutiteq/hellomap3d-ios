#ifndef BALLOONPOPUP_H_
#define BALLOONPOPUP_H_

#include "styles/BalloonPopupStyle.h"
#include "vectorelements/Popup.h"

#include <memory>

namespace Nuti {

/**
 * A highly configurable popup implementation that allows the user to specify a title, description, colors, images, font sizes etc.
 */
class BalloonPopup : public Popup {
public:
    /**
     * Constructs a BalloonPopup object with the specified style and attaches it to a billboard element.
     * If an empty string is passed for the title, it will not be drawn. The same applies to the description.
     * @param baseBillboard The billboard this balloon popup will be attached to.
     * @param style The style that defines what this balloon popup looks like.
     * @param title The text this balloon popup will display.
     * @param description The description this balloon popup will display.
     */
    BalloonPopup(const std::shared_ptr<Billboard>& baseBillboard, const std::shared_ptr<BalloonPopupStyle>& style,
                 const std::string& title, const std::string& desc);
    /**
     * Constructs a BalloonPopup object from a geometry object and a style.
     * If an empty string is passed for the title, it will not be drawn. The same applies to the description.
     * @param geometry The geometry object that defines the location of this balloon popup.
     * @param style The style that defines what this balloon popup looks like.
     * @param title The text this balloon popup will display.
     * @param description The description this balloon popup will display.
     */
    BalloonPopup(const std::shared_ptr<PointGeometry>& geometry, const std::shared_ptr<BalloonPopupStyle>& style,
                const std::string& title, const std::string& desc);
    /**
     * Constructs a BalloonPopup object from a map position and a style.
     * If an empty string is passed for the title, it will not be drawn. The same applies to the description.
     * @param poses The map position that defines the location of this balloon popup.
     * @param style The style that defines what this balloon popup looks like.
     * @param title The text this balloon popup will display.
     * @param description The description this balloon popup will display.
     */
    BalloonPopup(const MapPos& pos, const std::shared_ptr<BalloonPopupStyle>& style,
                 const std::string& title, const std::string& desc);
    virtual ~BalloonPopup();
    
    virtual std::shared_ptr<Bitmap> drawBitmap(const MapPos& anchorScreenPos,
                                               float screenWidth, float screenHeight, float dpToPX);
    
    /**
     * Returns the title of this balloon popup.
     * @return The title of this balloon popup.
     */
    std::string getTitle() const;
    /**
     * Sets the title this balloon popup will display. If an empty string is passed
     * the title will not be drawn.
     * @param title The new title this balloon popup will display.
     */
    void setTitle(const std::string& title);
    
    /**
     * Returns the description of this balloon popup.
     * @return The description of this balloon popup.
     */
    std::string getDescription() const;
    /**
     * Sets the description this balloon popup will display. If an empty string is passed
     * the description will not be drawn.
     * @param description The new description this balloon popup will display.
     */
    void setDescription(const std::string& desc);
    
    /**
     * Returns the style of this balloon popup.
     * @return The style that defines what this balloon popup looks like.
     */
	std::shared_ptr<BalloonPopupStyle> getStyle() const;
    /**
     * Sets the style for this balloon popup.
     * @return The new style that defines what this balloon popup looks like.
     */
	void setStyle(const std::shared_ptr<BalloonPopupStyle>& style);
    
private:
    static const int SCREEN_PADDING = 10;
    
    std::shared_ptr<BalloonPopupStyle> _style;
    
    std::string _title;
    std::string _desc;
    
};

}

#endif
