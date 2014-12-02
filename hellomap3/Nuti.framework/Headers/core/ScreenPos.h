#ifndef SCREENPOS_H_
#define SCREENPOS_H_

#include <string>
#include <cstddef>

namespace Nuti {
	
	/**
	 * A screen position defined by x,y floating point numbers.
	 */
	class ScreenPos {
	public:
		/**
		 * Constructs a ScreenPos object. All coordinates will be 0.
		 */
		ScreenPos();
		/**
		 * Constructs a ScreenPos object from 2 coordinates. 
		 * @param x The x coordinate.
		 * @param y The y coordinate.
		 */
		ScreenPos(float x, float y);
		
		/**
		 * Returns the x coordinate of this position.
		 * @return The x coordinate of this position.
		 */
		float getX() const;
		/**
		 * Sets the x coordinate of this tuple.
		 * @param x The new x coordinate of this tuple.
		 */
		void setX(float x);
		/**
		 * Returns the y coordinate of this position.
		 * @return The y coordinate of this position.
		 */
		float getY() const;
		/**
		 * Sets the y coordinate of this position.
		 * @param y The new y coordinate of this position.
		 */
		void setY(float y);
		
		/**
		 * Returns the n-th coordinate of this position.
		 * @param n The index of the requested coordinate.
		 * @return The n-th coordinate of this position.
		 */
		float operator[](std::size_t n) const;
		/**
		 * Returns a modifiable n-th coordinate of this position.
		 * @param n The index of the requested coordinate.
		 * @return The modifiable n-th coordinate of this position.
		 */
		float& operator[](std::size_t n);
		
		/**
		 * Sets the x and y coordinates of this position.
		 * @param x The new x coordinate of this position.
		 * @param y The new y coordinate of this position.
		 */
		void setCoords(float x, float y);

		/**
		 * Checks for equality between this and another screen position.
		 * @param p The other screen position.
		 * @return True if equal.
		 */
		bool operator==(const ScreenPos& p) const;
		/**
		 * Checks for inequality between this and another screen position.
		 * @param p The other screen position.
		 * @return True if not equal.
		 */
		bool operator!=(const ScreenPos& p) const;
		
		/**
		 * Creates a string representation of this screen position, useful for logging.
		 * @return The string representation of this screen position.
		 */
		std::string toString() const;
		
	protected:
		float _x;
		float _y;
	};
	
}

#endif
