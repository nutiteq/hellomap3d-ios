#ifndef MAPPOS_H_
#define MAPPOS_H_

#include "core/Tuple3D.h"

#include <string>

namespace Nuti {

class MapVec;

/**
 * A double precision map position defined using three coordinates. X and y coordinates denote positions on the map,
 * while z coordinate is height from the ground plane. Actual units for x, y and z depend on map projection.
 * For example, in EPSG:4326 x is used for latitude, y for longitude and z for height in meters.
 */
class MapPos : public Tuple3D {
public:
	/**
	 * Constructs a MapPos object. All coordinates will be 0.
	 */
	MapPos();
	/**
	 * Constructs a MapPos object from 2 coordinates. The z coordinate will be 0.
	 * @param x The x coordinate.
	 * @param y The y coordinate.
	 */
    MapPos(double x, double y);
    /**
	 * Constructs a MapPos object from 3 coordinates.
	 * @param x The x coordinate.
	 * @param y The y coordinate.
     * @param z The z coordinate.
	 */
	MapPos(double x, double y, double z);

	/**
	 * Adds another tuple to this map position.
	 * @param t The tuple to be added.
     * @return This map position after the addition.
	 */
	MapPos& operator+=(const Tuple3D& t);
	/**
	 * Subtracts another tuple from this map position.
	 * @param t The tuple to be subtracted.
    * @return This map position after the subtraction.
	 */
	MapPos& operator-=(const Tuple3D& t);

	/**
	 * Creates a new map position by adding a map vector to this map position.
	 * @param v The map vector to be added.
	 * @return The new map position.
	 */
	MapPos operator+(const MapVec& v) const;
	/**
	 * Creates a new map position by subtracting a map vector from this map position.
	 * @param v The map vector to be subtracted.
	 * @return The new map position.
	 */
	MapPos operator-(const MapVec& v) const;

	/**
	 * Creates a new map vector by subtracting a map position from this map position.
	 * @param p The map position to be subtracted.
	 * @return The new map vector.
	 */
	MapVec operator-(const MapPos& p) const;

	/**
     * Checks for equality between this and another map position.
     * @param p The other map position.
     * @return True if equal.
     */
	bool operator==(const MapPos& p) const;
    /**
     * Checks for inequality between this and another map position.
     * @param p The other map position.
     * @return True if not equal.
     */
	bool operator!=(const MapPos& p) const;

    /**
     * Calculates the distance between this and another map position.
     * @param p The other map position.
     * @return The distance between the two points.
     */
	double distanceFromPoint(const MapPos& p) const;
    /**
     * Calculates the square distance between this and another map position.
     * @param p The other map position.
     * @return The square distance between the two points.
     */
	double distanceSqrFromPoint(const MapPos& p) const;

    /**
     * Calculates the distance between this map position and an infinte line defined by two points.
     * @param a Some point on the infinte line.
     * @param b Another point on the infinite line.
     * @return The distance between this map position and the infinite line.
     */
	double distanceFromLine(const MapPos& a, const MapPos& b) const;
    /**
     * Calculates the square distance between this map position and an infinte line defined by two points.
     * @param a Some point on the infinte line.
     * @param b Another point on the infinite line.
     * @return The square distance between this map position and the infinite line.
     */
	double distanceSqrFromLine(const MapPos& a, const MapPos& b) const;
    
    /**
     * Calculates the distance between this map position and a line segment.
     * @param a Starting coordinate of the line segment.
     * @param b Ending coordinate of the line segment.
     * @return The distance between this map position and the line segment.
     */
    double distanceFromLineSegment(const MapPos& a, const MapPos& b) const;
    /**
     * Calculates the square distance between this map position and a line segment.
     * @param a Starting coordinate of the line segment.
     * @param b Ending coordinate of the line segment.
     * @return The square distance between this map position and the line segment.
     */
	double distanceSqrFromLineSegment(const MapPos& a, const MapPos& b) const;
    
    /**
     * Calculates the nearest point from this map position on a line segment.
     * @param a Starting coordinate of the line segment.
     * @param b Ending coordinate of the line segment.
     * @return The nearest point from this map position that lies on the line segment.
     */
    MapPos nearestPointOnLineSegment(const MapPos& a, const MapPos& b) const;

    /**
     * Rotates this map position around the z axis by an angle.
     * @param sin The sine value of the rotation angle.
     * @param cos The cosine value of the rotation angle.
     * @return This map position after the rotation.
     */
	MapPos& rotate2D(double sin, double cos);
    /**
     * Creates a new map position by rotating this map position around the z axis by an angle.
     * @param sin The sine value of the rotation angle.
     * @param cos The cosine value of the rotation angle.
     * @return The new rotated map position.
     */
	MapPos getRotated2D(double sin, double cos) const;

    /**
     * Creates a string representation of this map position, useful for logging.
     * @return The string representation of this map position.
     */
	std::string toString() const;
    
};
    
}

#endif
