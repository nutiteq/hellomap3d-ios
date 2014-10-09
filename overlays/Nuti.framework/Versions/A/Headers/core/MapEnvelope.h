#ifndef MAPENVELOPE_H_
#define MAPENVELOPE_H_

#include "core/MapBounds.h"

#include <memory>
#include <string>
#include <vector>

namespace Nuti {

class MapPos;

/**
 * A bounding area on the map. Can be defined by a map bounds object or by a convex bounding polygon.
 * This class is intended for conservative object area estimation and fast intersection testing.
 */
class MapEnvelope {
public:
    /**
	 * Constructs an empty MapEnvelope object. Nothing is contained within
     * this envelope.
	 */
	MapEnvelope();
    /**
	 * Constructs a MapEnvelope object using map bounds.
	 */
	MapEnvelope(const MapBounds& bounds);
    /**
	 * Constructs a MapEnvelope object from a convex bounding polygon.
	 */
	MapEnvelope(const std::vector<MapPos>& convexHull);
    /**
    * Copy constructs a MapEnvelope object from another map envelope by making a deep copy.
    * @param envelope The other map envelope.
    */
	MapEnvelope(const MapEnvelope& envelope);
	virtual ~MapEnvelope();

    /**
     * Deep copies another map envelope to this one.
     * @param envelope The other map envelope.
     * @return This map envelope after the deep copy.
     */
	MapEnvelope& operator=(const MapEnvelope& envelope);

    /**
     * Returns the map bounds of this map envelope.
     * @return The map bounds of this map envelope.
     */
	const MapBounds& getBounds() const;
    /**
     * Returns the convex hull of this map envelope, if it exists.
     * @return The convex hull of this map envelope if it exists or null if it doesn't.
     */
	const std::vector<MapPos>* getConvexHull() const;

    /**
     * Tests whether this map envelope contains another map envelope.
     * @param envelope The other map envelope.
     * @return True if this map envelope contains the other map envelope.
     */
	bool contains(const MapEnvelope& envelope) const;
    /**
     * Tests whether this map envelope intersects with another map envelope.
     * @param envelope The other map envelope.
     * @return True if this map envelope intersects the other map envelope.
     */
	bool intersects(const MapEnvelope& envelope) const;

    /**
     * Creates a string representation of this map envelope, useful for logging.
     * @return The string representation of this map envelope.
     */
	std::string toString() const;

private:
	MapBounds _bounds;

	std::unique_ptr<std::vector<MapPos> > _convexHull;
    
};

}

#endif
