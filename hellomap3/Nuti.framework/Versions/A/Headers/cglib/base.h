#ifndef cglib_base_h

#define cglib_base_h

#include <cstdlib>
#include <cstddef>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <limits>
#include <istream>
#include <ostream>

namespace cglib
{
	
	using std::size_t;
	
	/**
	 * Generic traits class for floating point operations.
	 */
	
	template <typename T>
		class float_traits
	{

	public:

		static inline T infinity() { if (!std::numeric_limits<T>::has_infinity) throw std::runtime_error("INFINITY is not representable"); return std::numeric_limits<T>::infinity(); }
		static inline T epsilon() { return 0; }
		static inline T sqrt(T val) { return static_cast<T>(std::sqrt(static_cast<double>(val))); }
		static inline T cos(T val) { return static_cast<T>(std::cos(static_cast<double>(val))); }
		static inline T sin(T val) { return static_cast<T>(std::sin(static_cast<double>(val))); }
		static inline T tan(T val) { return static_cast<T>(std::tan(static_cast<double>(val))); }
		static inline T acos(T val) { return static_cast<T>(std::acos(static_cast<double>(val))); }
		static inline T asin(T val) { return static_cast<T>(std::asin(static_cast<double>(val))); }
		static inline T atan2(T val1, T val2) { return static_cast<T>(std::atan2(static_cast<double>(val1), static_cast<double>(val2))); }
		static inline bool eq(T val1, T val2) { return val1 == val2; }
	};
	
	/**
	 * Specialized traits classes for float/double types.
	 */

	template <>
		class float_traits<float>
	{

	public:

		static inline float infinity() { return std::numeric_limits<float>::infinity(); }
		static inline float epsilon() { return 0; }
		static inline float sqrt(float val) { return std::sqrt(val); }
		static inline float cos(float val) { return std::cos(val); }
		static inline float sin(float val) { return std::sin(val); }
		static inline float tan(float val) { return std::tan(val); }
		static inline float acos(float val) { return std::acos(val); }
		static inline float asin(float val) { return std::asin(val);}
		static inline float atan2(float val1, float val2) { return std::atan2(val1, val2); }
		static inline bool eq(float val1, float val2) { return val1 == val2; }
	};

	template <>
		class float_traits<double>
	{

	public:

		static inline double infinity() { return std::numeric_limits<double>::infinity(); }
		static inline double epsilon() { return 0; }
		static inline double sqrt(double val) { return std::sqrt(val); }
		static inline double cos(double val) { return std::cos(val); }
		static inline double sin(double val) { return std::sin(val); }
		static inline double tan(double val) { return std::tan(val); }
		static inline double acos(double val) { return std::acos(val); }
		static inline double asin(double val) { return std::asin(val);}
		static inline double atan2(double val1, double val2) { return std::atan2(val1, val2); }
		static inline bool eq(double val1, double val2) { return val1 == val2; }
	};

}

#endif
