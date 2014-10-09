#ifndef MARKER_H_
#define MARKER_H_

#include "vectorelements/Billboard.h"

namespace Nuti {

class MarkerDrawData;
class MarkerStyle;

/**
 * A billboard element with a static bitmap that can be displayed on the map.
 */
class Marker : public Billboard {
public:
    /**
     * Constructs a Marker object with the specified style and attaches it to a billboard element.
     * @param baseBillboard The billboard this billboard will be attached to.
     * @param style The style that defines what this marker looks like.
     */
    Marker(const std::shared_ptr<Billboard>& baseBillboard, const std::shared_ptr<MarkerStyle>& style);
    /**
     * Constructs a Marker object from a geometry object and a style.
     * @param geometry The geometry object that defines the location of this marker.
     * @param style The style that defines what this marker looks like.
     */
	Marker(const std::shared_ptr<PointGeometry>& geometry, const std::shared_ptr<MarkerStyle>& style);
    /**
     * Constructs a Marker object from a map position and a style.
     * @param poses The map position that defines the location of this marker.
     * @param style The style that defines what this marker looks like.
     */
    Marker(const MapPos& pos, const std::shared_ptr<MarkerStyle>& style);
	virtual ~Marker();
    
    /**
     * Returns the style of this marker.
     * @return The style that defines what this marker looks like.
     */
	virtual std::shared_ptr<MarkerStyle> getStyle() const;
    /**
     * Sets the style for this marker.
     * @return The new style that defines what this marker looks like.
     */
	void setStyle(const std::shared_ptr<MarkerStyle>& style);
    
private:
	std::shared_ptr<MarkerStyle> _style;

};

}

#endif
