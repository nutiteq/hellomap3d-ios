#ifndef TUPLE3D_H_
#define TUPLE3D_H_

#include <string>

namespace Nuti {

/**
 * An abstract base class for MapVec and MapPos.
 */
class Tuple3D {
public:
    virtual ~Tuple3D();
    /**
     * Returns the x coordinate of this tuple.
     * @return The x coordinate of this tuple.
     */
	double getX() const;
    /**
     * Sets the x coordinate of this tuple.
     * @param x The new x coordinate of this tuple.
     */
	void setX(double x);
    /**
     * Returns the y coordinate of this tuple.
     * @return The y coordinate of this tuple.
     */
	double getY() const;
    /**
     * Sets the y coordinate of this tuple.
     * @param y The new y coordinate of this tuple.
     */
	void setY(double y);
    /**
     * Returns the z coordinate of this tuple.
     * @return The z coordinate of this tuple.
     */
	double getZ() const;
    /**
     * Sets the z coordinate of this tuple.
     * @param z The new z coordinate of this tuple.
     */
	void setZ(double z);

    /**
     * Returns the n-th coordinate of this tuple.
     * @param n The index of the requested coordinate.
     * @return The n-th coordinate of this tuple.
     */
	double operator[](std::size_t n) const;
    /**
     * Returns a modifiable n-th coordinate of this tuple.
     * @param n The index of the requested coordinate.
     * @return The modifiable n-th coordinate of this tuple.
     */
	double &operator[](std::size_t n);

    /**
     * Sets the x and y coordinates of this tuple.
     * @param x The new x coordinate of this tuple.
     * @param y The new y coordinate of this tuple.
     */
	void setCoords(double x, double y);
    /**
     * Sets the x, y and z coordinates of this tuple.
     * @param x The new x coordinate of this tuple.
     * @param y The new y coordinate of this tuple.
     * @param z The new z coordinate of this tuple.
     */
	void setCoords(double x, double y, double z);

    /**
     * An abstract method for creating a string representation of a this tuple, useful for logging.
     * @return The string representation of this tuple.
     */
	virtual std::string toString() const = 0;
    
protected:
	Tuple3D();
    Tuple3D(double x, double y);
	Tuple3D(double x, double y, double z);
    
    Tuple3D& rotate2D(double sin, double cos);

	double _x;
	double _y;
	double _z;
    
};

}

#endif
