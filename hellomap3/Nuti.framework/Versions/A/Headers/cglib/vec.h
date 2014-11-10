#ifndef cglib_vec_h

#define cglib_vec_h

#include "base.h"

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
		
	protected:
		
		T _col[N];

	public:

		typedef T value_type;
		typedef Traits traits_type;
		
		inline vec() { }
		
		inline vec(const vec<T, N, Traits> & v)
		{
			for (size_t i = 0; i < N; i++) // *this = v;
			{
				_col[i] = v._col[i];
			}
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
			for (size_t i = 0; i < N; i++)
			{
				_col[i] = *data++;
			}
			return *this;
		}
		
		inline vec<T, N, Traits> operator - () const
		{
			vec<T, N, Traits> neg;
			for (size_t i = 0; i < N; i++)
			{
				neg._col[i] = -_col[i];
			}
			return neg;
		}
		
		inline vec<T, N, Traits> & operator = (const vec<T, N, Traits> & v)
		{
			for (size_t i = 0; i < N; i++)
			{
				_col[i] = v._col[i];
			}
			return *this;
		}
		
		inline vec<T, N, Traits> & operator += (const vec<T, N, Traits> & v)
		{
			for (size_t i = 0; i < N; i++)
			{
				_col[i] += v._col[i];
			}
			return *this;
		}
		
		inline vec<T, N, Traits> & operator -= (const vec<T, N, Traits> & v)
		{
			for (size_t i = 0; i < N; i++)
			{
				_col[i] -= v._col[i];
			}
			return *this;
		}
		
		inline vec<T, N, Traits> & operator *= (T val)
		{
			for (size_t i = 0; i < N; i++)
			{
				_col[i] *= val;
			}
			return *this;
		}
		
		inline void clear()
		{
			for (size_t i = 0; i < N; i++)
			{
				_col[i] = 0;
			}
		}
		
		inline static vec<T, N, Traits> zero()
		{
			vec<T, N, Traits> v;
			for (size_t i = 0; i < N; i++)
			{
				v._col[i] = 0;
			}
			return v;
		}
		
		static vec<T, N, Traits> unit(size_t n)
		{
			vec<T, N, Traits> v;
			for (size_t i = 0; i < N; i++)
			{
				v._col[i] = static_cast<T>(i == n ? 1 : 0);
			}
			return v;
		}
		
		template <typename S, typename TraitsS>
			static vec<T, N, Traits> convert(const vec<S, N, TraitsS> & v)
		{
			vec<T, N, Traits> w;
			for (size_t i = 0; i < N; i++)
			{
				w._col[i] = static_cast<T>(v[i]);
			}
			return w;
		}
		
	};
	
	/**
	 * Calculates dot product of two vectors. Note that vectors do not
	 * have to be of same length!
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline T
		dot_product(const vec<T, N, Traits> & v1, const vec<T, N, Traits> & v2)
	{
		T sp = 0;
		for (size_t i = 0; i < N; i++)
		{
			sp += v1(i) * v2(i);
		}
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
	 * Normalizes non-zero vector, ie finds vector with same direction
	 * but unit length. On zero vector, returns zero vector.
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline vec<T, N, Traits> 
		unit0(const vec<T, N, Traits> & v)
	{
		T len = length(v);
		if (Traits::eq(len, 0))
			return vec<T, N, Traits>::zero();
		return unit(v);
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
		expand(const vec<T, N, Traits> & v, T last = T())
	{
		vec<T, N+1, Traits> w;
		for (size_t i = 0; i < N; i++)
		{
			w(i) = v(i);
		}
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
		for (size_t i = 0; i < N - 1; i++)
		{
			w(i) = v(i);
		}
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
		for (size_t i = 0; i < N - 1; i++)
		{
			w(i) = v(i) * invcoeff;
		}
		return w;
	}
	
	/**
	 * Perspective projection (divides vector with last element and drops it then).
	 * If last element is zero, returns zero vector.
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline vec<T, N-1, Traits>
		proj_p0(const vec<T, N, Traits> & v)
	{
		T coeff = v(N - 1);
		if (Traits::eq(coeff, 0))
			return vec<T, N-1, Traits>::zero();
		return proj_p(v);
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
		for (size_t i = 0; i < N; i++)
		{
			w(i) = v(i) * invcoeff;
		}
		return w;
	}
	
	/**
	 * Perspective projection (divides vector with last element but does not drop it).
	 * If last element is zero, returns zero vector.
	 * @relates vec
	 */
	
	template <typename T, size_t N, typename Traits> inline vec<T, N, Traits>
		div_p0(const vec<T, N, Traits> & v)
	{
		T coeff = v(N - 1);
		if (Traits::eq(coeff, 0))
			return vec<T, N, Traits>::zero();
		return div_p(v);
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
	 * Derived vector instances for 2D, 3D and 4D cases
	 */
	
	template <typename T, typename Traits = float_traits<T> >
		class vec2 : public vec<T, 2, Traits>
	{
		
	public:
		
		inline vec2()
		{
#ifdef CGLIB_CLEAR
			clear();
#endif
		}
		inline vec2(const vec<T, 2, Traits> & v)
		{
			this->_col[0] = v(0); this->_col[1] = v(1);
		}
		inline explicit vec2(T s1, T s2)
		{
			this->_col[0] = s1; this->_col[1] = s2;
		}

		inline vec2<T, Traits> & operator = (const vec<T, 2, Traits> & v)
		{
			this->_col[0] = v(0); this->_col[1] = v(1);
			return *this;
		}
	};

	template <typename T, typename Traits = float_traits<T> >
		class vec3 : public vec<T, 3, Traits>
	{
		
	public:
		
		inline vec3()
		{
#ifdef CGLIB_CLEAR
			clear();
#endif
		}
		inline vec3(const vec<T, 3, Traits> & v)
		{
			this->_col[0] = v(0); this->_col[1] = v(1); this->_col[2] = v(2);
		}
		inline explicit vec3(T s1, T s2, T s3)
		{
			this->_col[0] = s1; this->_col[1] = s2; this->_col[2] = s3;
		}

		inline vec3<T, Traits> & operator = (const vec<T, 3, Traits> & v)
		{
			this->_col[0] = v(0); this->_col[1] = v(1); this->_col[2] = v(2);
			return *this;
		}
	};

	template <typename T, typename Traits = float_traits<T> >
		class vec4 : public vec<T, 4, Traits>
	{
		
	public:
		
		inline vec4()
		{
#ifdef CGLIB_CLEAR
			clear();
#endif
		}
		inline vec4(const vec<T, 4, Traits> & v)
		{
			this->_col[0] = v(0); this->_col[1] = v(1); this->_col[2] = v(2); this->_col[3] = v(3);
		}
		inline explicit vec4(T s1, T s2, T s3, T s4)
		{
			this->_col[0] = s1; this->_col[1] = s2; this->_col[2] = s3; this->_col[3] = s4;
		}

		inline vec4<T, Traits> & operator = (const vec<T, 4, Traits> & v)
		{
			this->_col[0] = v(0); this->_col[1] = v(1); this->_col[2] = v(2); this->_col[3] = v(3);
			return *this;
		}
	};

}

#endif
