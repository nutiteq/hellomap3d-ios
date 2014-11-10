#ifndef MAPBOUNDS_H_
#define MAPBOUNDS_H_

#include "core/MapPos.h"
#include "core/MapVec.h"

#include <string>

namespace Nuti {

/**
 * A container class that defines an axis aligned cuboid on the map using minimum and maximum map positions.
 * Valid ranges for map bounds depend on the projection used.
 */
class MapBounds {
public:
    /**
	 * Constructs an empty MapBounds object. The coordinates of the minimum map position will be 
     * set to positive infinity and the coordinates of the maximum map position will be
     * set to negative infinity.
	 */
	MapBounds();
    /**
	 * Constructs a MapBounds object from a minimum and maximum map position. If a coordinate of the 
     * minimum map positon is larger than the same coordinate of the maximum map position then those
     * coordinates will be swapped.
     * @param min The minimum map position.
	 * @param max The maximum map position.
	 */
	MapBounds(const MapPos& min, const MapPos& max);
	virtual ~MapBounds();

    /**
     * Checks for equality between this and another map bounds object.
     * @param mapBounds The other map bounds object.
     * @return True if equal.
     */
	bool operator==(const MapBounds& mapBounds) const;
    /**
     * Checks for inequality between this and another map bounds object.
     * @param mapBounds The other map bounds object.
     * @return True if not equal.
     */
	bool operator!=(const MapBounds& mapBounds) const;
    
    /**
	 * Sets the minimum and maximum map positions of this map bounds object. If a coordinate of the
     * minimum map positon is larger than the same coordinate of the maximum map position then those
     * coordinates will be swapped.
     * @param min The minimum map position.
	 * @param max The maximum map position.
	 */
    void setBounds(const MapPos& min, const MapPos& max);
    
    /**
	 * Calculates the center map position of this map envelope object.
     * @return The center postion if this map envelope object.
	 */
    MapPos getCenter() const;
    
    /**
	 * Calculates the difference vector between the maximum and minimum map positions of this map bounds object.
     * @return The difference vector between maximum and minimum map positions of this map bounds object.
	 */
	MapVec getDelta() const;

    /**
     * Returns the minimum map position of this map envelope object.
     * @return The minimum map position of this map envelope object.
     */
	const MapPos& getMin() const;
    /**
     * Returns the modifiable minimum map position of this map envelope object.
     * @return The modifiable minimum map position of this map envelope object.
     */
	MapPos& getMin();

    /**
     * Returns the maximum map position of this map envelope object.
     * @return The maximum map position of this map envelope object.
     */
	const MapPos& getMax() const;
    /**
     * Returns the modifiable maximum map position of this map envelope object.
     * @return The modifiable maximum map position of this map envelope object.
     */
	MapPos& getMax();

    /**
     * Tests whether this map bounds object contains a map position.
     * @param pos The map position.
     * @return True if this map bounds object contains the map position.
     */
	bool contains(const MapPos& pos) const;
    /**
     * Tests whether this map bounds object contains a another map bounds object.
     * @param bounds The other map bounds object.
     * @return True if this map bounds object contains the other map bounds object.
     */
    bool contains(const MapBounds& bounds) const;
    /**
     * Tests whether this map bounds object intersects with a another map bounds object.
     * @param bounds The other map bounds object.
     * @return True if this map bounds object intersects with the other map bounds object.
     */
    bool intersects(const MapBounds& bounds) const;
    
    /**
     * Expands this map bounds object to contain a map position.
     * @param pos The map position.
     */
    void expandToContain(const MapPos& pos);
    /**
     * Expands this map bounds object to contain another map bounds object.
     * @param bounds The other map bounds object.
     */
    void expandToContain(const MapBounds& bounds);

    /**
     * Creates a string representation of this map bounds object, useful for logging.
     * @return The string representation of this map bounds object.
     */
	std::string toString() const;
    
private:
	MapPos _min;
	MapPos _max;
    
};

}

#endif
