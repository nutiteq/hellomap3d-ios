#ifndef _CGLIB_VEC_H
#define _CGLIB_VEC_H

#include "base.h"

#include <array>
#include <initializer_list>

namespace cglib
{
	
	/**
	 * A vector of type T with size N.
	 * T is not required to be, but is nevertheless assumed to be
	 * one of the built-in floating point types (float, double).
	 * N is assumed to be 2 or 3.
	 */
	
	template <typename T, size_t N, typename Traits = float_traits<T> >
		class vec
	{
		
	public:

		typedef T value_type;
		typedef Traits traits_type;
		typedef T * iterator;
		typedef const T * const_iterator;

		inline vec() = default;
		
#if defined(__clang__) // XCode 7.2 seems to generate buggy code for ARM64 for default constructor
		inline vec(const vec<T, N, Traits> & v)
		{
			for_each_unrolled<N>([&](size_t i)
			{
				_col[i] = v._col[i];
			});
		}
#endif

		inline explicit vec(const std::array<T, N> & col)
		{
			for_each_unrolled<N>([&](size_t i)
			{
				_col[i] = col[i];
			});
		}
		
#if defined(_MSC_VER) && _MSC_VER < 1900 // VS2013 and older compilers do not support {} initialization
		inline explicit vec(T x, T y)
		{
			static_assert(N == 2, "Wrong number of constructor arguments");
			_col[0] = x; _col[1] = y;
		}

		inline explicit vec(T x, T y, T z)
		{
			static_assert(N == 3, "Wrong number of constructor arguments");
			_col[0] = x; _col[1] = y; _col[2] = z;
		}

		inline explicit vec(T x, T y, T z, T w)
		{
			static_assert(N == 4, "Wrong number of constructor arguments");
			_col[0] = x; _col[1] = y; _col[2] = z; _col[3] = w;
		}
#else
		inline explicit vec(T x, T y) : _col { x, y }
		{
			static_assert(N == 2, "Wrong number of constructor arguments");
		}

		inline explicit vec(T x, T y, T z) : _col { x, y, z }
		{
			static_assert(N == 3, "Wrong number of constructor arguments");
		}

		inline explicit vec(T x, T y, T z, T w) : _col { x, y, z, w }
		{
			static_assert(N == 4, "Wrong number of constructor arguments");
		}
#endif

		inline vec(std::initializer_list<T> list)
		{
			assert(list.size() == N);
			for_each_unrolled<N>([&](size_t i)
			{
				_col[i] = *(list.begin() + i);
			});
		}
		
		inline T operator () (size_t c) const
		{
			assert(c < N);
			return _col[c];
		}
		
		inline T & operator () (size_t c)
		{
			assert(c < N);
			return _col[c];
		}
		
		inline T operator [] (size_t c) const
		{
			return (*this)(c);
		}
		
		inline T & operator [] (size_t c)
		{
			return (*this)(c);
		}
		
		inline iterator begin()
		{
			return &_col[0];
		}
		
		inline iterator end()
		{
			return &_col[0] + N;
		}
		
		inline const_iterator cbegin() const
		{
			return &_col[0];
		}
		
		inline const_iterator cend() const
		{
			return &_col[0] + N;
		}
		
		inline const T * data() const
		{
			return &_col[0];
		}
		
		inline T * data()
		{
			return &_col[0];
		}

		inline vec<T, N, Traits> & copy(const T * data)
		{
			for_each_unrolled<N>([&](size_t i)
			{
				_col[i] = data[i];
			});
			return *this;
		}
		
		inline vec<T, N, Traits> operator - () const
		{
			vec<T, N, Traits> neg;
			for_each_unrolled<N>([&](size_t i)
			{
				neg._col[i] = -_col[i];
			});
			return neg;
		}
		
		inline vec<T, N, Traits> & operator += (const vec<T, N, Traits> & v)
		{
			for_each_unrolled<N>([&](size_t i)
			{
				_col[i] += v._col[i];
			});
			return *this;
		}
		
		inline vec<T, N, Traits> & operator -= (const vec<T, N, Traits> & v)
		{
			for_each_unrolled<N>([&](size_t i)
			{
				_col[i] -= v._col[i];
			});
			return *this;
		}
		
		inline vec<T, N, Traits> & operator *= (T val)
		{
			for_each_unrolled<N>([&](size_t i)
			{
				_col[i] *= val;
			});
			return *this;
		}
		
		inline void clear()
		{
			for_each_unrolled<N>([&](size_t i)
			{
				_col[i] = 0;
			});
		}
		
		inline void swap(vec<T, N, Traits> & v)
		{
			for_each_unrolled<N>([&](size_t i)
			{
				std::swap(_col[i], v._col[i]);
			});
		}
		
		inline static vec<T, N, Traits> zero()
		{
			vec<T, N, Traits> v;
			for_each_unrolled<N>([&](size_t i)
			{
				v._col[i] = 0;
			});
			return v;
		}
		
		static vec<T, N, Traits> axis(size_t n)
		{
			vec<T, N, Traits> v;
			for_each_unrolled<N>([&](size_t i)
			{
				v._col[i] = static_cast<T>(i == n ? 1 : 0);
			});
			return v;
		}
		
		template <typename S, typename TraitsS>
			static vec<T, N, Traits> convert(const vec<S, N, TraitsS> & v)
		{
			vec<T, N, Traits> w;
			for_each_unrolled<N>([&](size_t i)
			{
				w._col[i] = static_cast<T>(v[i]);
			});
			return w;
		}
		
	private:
		
		T _col[N];
	};
	
	/**
	 * Calculates dot product of two vectors.
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline T
		dot_product(const vec<T, N, Traits> & v1, const vec<T, N, Traits> & v2)
	{
		T sp = 0;
		for_each_unrolled<N>([&](size_t i)
		{
			sp += v1(i) * v2(i);
		});
		return sp;
	}
	
	/**
	 * Calculates vector product of two vectors. Defined only for N=3, N=4.
	 * @relates vec
	 */
	
	template <typename T, typename Traits> inline vec<T, 3, Traits>
		vector_product(const vec<T, 3, Traits> & v1, const vec<T, 3, Traits> & v2)
	{
		vec<T, 3, Traits> vp;
		vp(0) = v1(1) * v2(2) - v1(2) * v2(1);
		vp(1) = v1(2) * v2(0) - v1(0) * v2(2);
		vp(2) = v1(0) * v2(1) - v1(1) * v2(0);
		return vp;
	}
	
	template <typename T, typename Traits> inline vec<T, 4, Traits>
		vector_product(const vec<T, 4, Traits> & v1, const vec<T, 4, Traits> & v2)
	{
		vec<T, 4, Traits> vp;
		vp(0) = v1(1) * v2(2) - v1(2) * v2(1);
		vp(1) = v1(2) * v2(0) - v1(0) * v2(2);
		vp(2) = v1(0) * v2(1) - v1(1) * v2(0);
		vp(3) = 0;
		return vp;
	}
	
	/**
	 * Normalizes non-zero vector, ie finds vector with same direction
	 * but unit length. On zero vector, result is not defined.
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> vec<T, N, Traits>
		unit(const vec<T, N, Traits> & v)
	{
		T len = length(v), invlen;
		if (Traits::eq(len, 0))
			invlen = Traits::infinity();
		else
			invlen = 1 / len;
		return v * invlen;
	}

	/**
	 * @relates vec
	 */

	template <typename T, size_t N, typename Traits> inline T
		norm(const vec<T, N, Traits> & v)
	{
		return dot_product(v, v);
	}
	
	/**
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> T
		length(const vec<T, N, Traits> & v)
	{
		return Traits::sqrt(norm(v));
	}

	/**
	 * Expand vector (add last element).
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline vec<T, N+1, Traits>
		expand(const vec<T, N, Traits> & v, T last = 0)
	{
		vec<T, N+1, Traits> w;
		for_each_unrolled<N>([&](size_t i)
		{
			w(i) = v(i);
		});
		w(N) = last;
		return w;
	}
	
	/**
	 * Orthogonal projection (drops last element).
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline vec<T, N-1, Traits>
		proj_o(const vec<T, N, Traits> & v)
	{
		vec<T, N-1, Traits> w;
		for_each_unrolled<N-1>([&](size_t i)
		{
			w(i) = v(i);
		});
		return w;
	}
	
	/**
	 * Perspective projection (divides vector with last element and drops it then).
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> vec<T, N-1, Traits>
		proj_p(const vec<T, N, Traits> & v)
	{
		T coeff = v(N - 1), invcoeff;
		if (Traits::eq(coeff, 0))
			invcoeff = Traits::infinity();
		else
			invcoeff = 1 / coeff;
		vec<T, N-1, Traits> w;
		for_each_unrolled<N-1>([&](size_t i)
		{
			w(i) = v(i) * invcoeff;
		});
		return w;
	}
	
	/**
	 * Perspective projection (divides vector with last element but does not drop it).
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> vec<T, N, Traits>
		div_p(const vec<T, N, Traits> & v)
	{
		T coeff = v(N - 1), invcoeff;
		if (Traits::eq(coeff, 0))
			invcoeff = Traits::infinity();
		else
			invcoeff = 1 / coeff;
		vec<T, N, Traits> w;
		for_each_unrolled<N>([&](size_t i)
		{
			w(i) = v(i) * invcoeff;
		});
		return w;
	}
	
	/**
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline bool
		operator == (const vec<T, N, Traits> & v1, const vec<T, N, Traits> & v2)
	{
		for (size_t i = 0; i < N; i++)
		{
			if (!Traits::eq(v1(i), v2(i)))
				return false;
		}
		return true;
	}
	
	/**
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline bool
		operator != (const vec<T, N, Traits> & v1, const vec<T, N, Traits> & v2)
	{
		return !(v1 == v2);
	}
	
	/**
	 * Intended for containers only!
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline bool
		operator < (const vec<T, N, Traits> & v1, const vec<T, N, Traits> & v2)
	{
		for (size_t i = 0; i < N; i++)
		{
			if (v1(i) < v2(i))
				return true;
			if (v2(i) < v1(i))
				return false;
		}
		return false;
	}

	/**
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline vec<T, N, Traits>
		operator + (const vec<T, N, Traits> & v1, const vec<T, N, Traits> & v2)
	{
		vec<T, N, Traits> vs(v1);
		return vs += v2;
	}
	
	/**
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline vec<T, N, Traits>
		operator - (const vec<T, N, Traits> & v1, const vec<T, N, Traits> & v2)
	{
		vec<T, N, Traits> vd(v1);
		return vd -= v2;
	}
	
	/**
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline vec<T, N, Traits>
		operator * (const vec<T, N, Traits> & v, T s)
	{
		vec<T, N, Traits> vm(v);
		return vm *= s;
	}
	
	/**
	 * Reads vector from stream, assumes follwing format: (x1, ..., xN).
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits, typename CharT, typename CharTraits> std::basic_istream<CharT, CharTraits> &
		operator >> (std::basic_istream<CharT, CharTraits> & is, vec<T, N, Traits> & v)
	{
		CharT ch;
		is >> ch;
		if (ch == '(')
		{
			size_t i = 0;
			do
			{
				if (i >= N)
					break;
				is >> v(i++);
				is >> ch;
			} while (ch == ',');
			if (ch != ')')
			{
				is.setstate(std::ios_base::failbit);
			}
		}
		else
		{
			is.setstate(std::ios_base::failbit);
		}
		return is;
	}
	
	/**
	 * Writes vector to stream, uses follwing format: (x1, ..., xN).
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits, typename CharT, typename CharTraits> std::basic_ostream<CharT, CharTraits> &
		operator << (std::basic_ostream<CharT, CharTraits> & os, const vec<T, N, Traits> & v)
	{
		os << '(';
		for (size_t i = 0; i < N; i++)
		{
			if (i > 0)
			{
				os << ',';
			}
			os << v(i);
		}
		os << ')';
		return os;
	}

	/**
	 * Commonly used instances for 2D, 3D and 4D cases
	 */
	
	template <typename T, typename Traits = float_traits<T> > using vec2 = vec<T, 2, Traits>;
	template <typename T, typename Traits = float_traits<T> > using vec3 = vec<T, 3, Traits>;
	template <typename T, typename Traits = float_traits<T> > using vec4 = vec<T, 4, Traits>;

}

#endif
