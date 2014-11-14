#ifndef cglib_mat_h

#define cglib_mat_h

#include "vec.h"

namespace cglib
{

	/**
	 * A square matrix of type T with N rows and N columns.
	 * T is assumed to be float or double (although should work in other
	 * instances also).
	 */
	
	template <typename T, size_t N, typename Traits = float_traits<T> >
		class mat
	{

	protected:

		T _colrow[N][N];

	public:
		
		typedef T value_type;
		typedef Traits traits_type;

		inline mat() { }
		
		inline mat(const mat<T, N, Traits> & m) { *this = m; }
		
		inline T operator () (size_t r, size_t c) const
		{
			return _colrow[c][r];
		}
		
		inline T & operator () (size_t r, size_t c)
		{
			return _colrow[c][r];
		}

		inline const T * data() const
		{
			return &_colrow[0][0];
		}
		
		inline T * data()
		{
			return &_colrow[0][0];
		}
		
		mat<T, N, Traits> & copy(const T * data)
		{
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					_colrow[i][j] = *data++;
				}
			}
			return *this;
		}
		
		mat<T, N, Traits> & copy_row(size_t j, const T * data)
		{
			for (size_t i = 0; i < N; i++)
			{
				_colrow[i][j] = *data++;
			}
			return *this;
		}
		
		mat<T, N, Traits> & copy_col(size_t i, const T * data)
		{
			for (size_t j = 0; j < N; j++)
			{
				_colrow[i][j] = *data++;
			}
			return *this;
		}
		
		mat<T, N, Traits> operator - () const
		{
			mat<T, N, Traits> neg;
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					neg._colrow[i][j] = -_colrow[i][j];
				}
			}
			return neg;
		}
		
		mat<T, N, Traits> & operator = (const mat<T, N, Traits> & m)
		{
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					_colrow[i][j] = m._colrow[i][j];
				}
			}
			return *this;
		}
		
		mat<T, N, Traits> & operator += (const mat<T, N, Traits> & m)
		{
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					_colrow[i][j] += m._colrow[i][j];
				}
			}
			return *this;
		}
		
		mat<T, N, Traits> & operator -= (const mat<T, N, Traits> & m)
		{
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					_colrow[i][j] -= m._colrow[i][j];
				}
			}
			return *this;
		}
		
		mat<T, N, Traits> & operator *= (T val)
		{
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					_colrow[i][j] *= val;
				}
			}
			return *this;
		}

		mat<T, N, Traits> & operator *= (const mat<T, N, Traits> & m2)
		{
			mat<T, N, Traits> m1(*this);
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					T s = 0;
					for (size_t k = 0; k < N; k++)
					{
						s += m1(i, k) * m2(k, j);
					}
					_colrow[j][i] = s;
				}
			}
			return *this;
		}

		mat<T, N, Traits> & operator /= (const mat<T, N, Traits> & m)
		{
			mat<T, N, Traits> m2(inverse(m));
			return (*this) *= m2;
		}

		void clear()
		{
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					_colrow[i][j] = 0;
				}
			}
		}

		static mat<T, N, Traits> zero()
		{
			mat<T, N, Traits> m;
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					m._colrow[i][j] = 0;
				}
			}
			return m;
		}

		static mat<T, N, Traits> identity()
		{
			mat<T, N, Traits> m;
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					m._colrow[i][j] = (T) (i == j ? 1 : 0);
				}
			}
			return m;
		}

		static mat<T, N, Traits> flip(size_t i)
		{
			mat<T, N, Traits> m = identity();
			m(i, i) = -m(i, i);
			return m;
		}

		template <typename S, typename TraitsS>
			static mat<T, N, Traits> convert(const mat<S, N, TraitsS> & m)
		{
			mat<T, N, Traits> n;
			for (size_t i = 0; i < N; i++)
			{
				for (size_t j = 0; j < N; j++)
				{
					n._colrow[i][j] = static_cast<T>(m(j, i));
				}
			}
			return n;
		}

	};

	/**
	 * Create vector from a fixed matrix column.
	 * @relates vec
	 */

	template <typename T, size_t N, typename Traits> inline vec<T, N, Traits>
		col_vector(const mat<T, N, Traits> & m, size_t c)
	{
		vec<T, N, Traits> v;
		for (size_t i = 0; i < N; i++)
		{
			v(i) = m(i, c);
		}
		return v;
	}

	/**
	 * Create vector from a fixed matrix row.
	 * @relates vec
	 */

	template <typename T, size_t N, typename Traits> inline vec<T, N, Traits>
		row_vector(const mat<T, N, Traits> & m, size_t r)
	{
		vec<T, N, Traits> v;
		for (size_t i = 0; i < N; i++)
		{
			v(i) = m(r, i);
		}
		return v;
	}

	
	/**
	 * Calculates 3x3 matrix N for 3D vector V such that
	 * N*W=VxW for all vectors W.
	 * @relates mat
	 */
	
	template <typename T, typename Traits> inline mat<T, 3, Traits>
		star_matrix(const vec<T, 3, Traits> & v)
	{
		mat<T, 3, Traits> m;
		m(0, 0) = 0;	 m(0, 1) = -v(2); m(0, 2) = v(1);
		m(1, 0) =  v(2); m(1, 1) = 0;	  m(1, 2) = -v(0);
		m(2, 0) = -v(1); m(2, 1) = v(0);  m(2, 2) = 0;
		return m;
	}

	/**
	 * Gives scaling matrix for given scaling coefficents.
	 * @relates mat
	 */

	template <typename T, typename Traits> inline mat<T, 3, Traits>
		scale3_matrix(const vec<T, 3, Traits> & s)
	{
		mat<T, 3, Traits> m;
		m(0, 0) = s(0);	 m(0, 1) = 0;    m(0, 2) = 0;
		m(1, 0) = 0;     m(1, 1) = s(1); m(1, 2) = 0;
		m(2, 0) = 0;     m(2, 1) = 0;    m(2, 2) = s(2);
		return m;
	}

	/**
	 * Gives scaling matrix for given scaling coefficents.
	 * @relates mat
	 */

	template <typename T, typename Traits> inline mat<T, 4, Traits>
		scale4_matrix(const vec<T, 3, Traits> & s)
	{
		mat<T, 4, Traits> m;
		m(0, 0) = s(0);	 m(0, 1) = 0;    m(0, 2) = 0;    m(0, 3) = 0;
		m(1, 0) = 0;     m(1, 1) = s(1); m(1, 2) = 0;    m(1, 3) = 0;
		m(2, 0) = 0;     m(2, 1) = 0;    m(2, 2) = s(2); m(2, 3) = 0;
		m(3, 0) = 0;     m(3, 1) = 0;    m(3, 2) = 0;    m(3, 3) = 1;
		return m;
	}

	/**
	 * Gives translation matrix for given translation vector.
	 * @relates mat
	 */

	template <typename T, typename Traits> inline mat<T, 3, Traits>
		translate3_matrix(const vec<T, 3, Traits> & t)
	{
		mat<T, 3, Traits> m;
		m(0, 0) = 1;	 m(0, 1) = 0;    m(0, 2) = t(0);
		m(1, 0) = 0;     m(1, 1) = 1;    m(1, 2) = t(1);
		m(2, 0) = 0;     m(2, 1) = 0;    m(2, 2) = t(2);
		return m;
	}

	/**
	 * Gives translation matrix for given translation vector.
	 * @relates mat
	 */

	template <typename T, typename Traits> inline mat<T, 4, Traits>
		translate4_matrix(const vec<T, 3, Traits> & t)
	{
		mat<T, 4, Traits> m;
		m(0, 0) = 1;	 m(0, 1) = 0;    m(0, 2) = 0;    m(0, 3) = t(0);
		m(1, 0) = 0;     m(1, 1) = 1;    m(1, 2) = 0;    m(1, 3) = t(1);
		m(2, 0) = 0;     m(2, 1) = 0;    m(2, 2) = 1;    m(2, 3) = t(2);
		m(3, 0) = 0;     m(3, 1) = 0;    m(3, 2) = 0;    m(3, 3) = 1;
		return m;
	}

	/**
	 * Gives Euler matrix for given "head, pitch, bank" parameters.
	 * @relates mat
	 */

	template <typename T, typename Traits> inline mat<T, 3, Traits>
		euler3_matrix(const vec<T, 3, Traits> & hpb)
	{
		mat<T, 3, Traits> m;
		T sh = Traits::sin(hpb(0)), ch = Traits::cos(hpb(0));
		T sp = Traits::sin(hpb(1)), cp = Traits::cos(hpb(1));
		T sb = Traits::sin(hpb(2)), cb = Traits::cos(hpb(2));
		m(0, 0) =  cb*ch - sb*sp*sh;
		m(0, 1) = -sb*cp;
		m(0, 2) =  cb*sh + sb*sp*ch;
		m(1, 0) =  sb*ch + cb*sp*sh;
		m(1, 1) =  cb*cp;
		m(1, 2) =  sb*sh - cb*sp*ch;
		m(2, 0) = -cp*sh;
		m(2, 1) =  sp;
		m(2, 2) =  cp*ch;
		return m;
	}

	/**
	 * Gives Euler matrix for given "head, pitch, bank" parameters.
	 * @relates mat
	 */

	template <typename T, typename Traits> inline mat<T, 4, Traits>
		euler4_matrix(const vec<T, 3, Traits> & hpb)
	{
		mat<T, 4, Traits> m;
		T sh = Traits::sin(hpb(0)), ch = Traits::cos(hpb(0));
		T sp = Traits::sin(hpb(1)), cp = Traits::cos(hpb(1));
		T sb = Traits::sin(hpb(2)), cb = Traits::cos(hpb(2));
		m(0, 0) =  cb*ch - sb*sp*sh;
		m(0, 1) = -sb*cp;
		m(0, 2) =  cb*sh + sb*sp*ch;
		m(1, 0) =  sb*ch + cb*sp*sh;
		m(1, 1) =  cb*cp;
		m(1, 2) =  sb*sh - cb*sp*ch;
		m(2, 0) = -cp*sh;
		m(2, 1) =  sp;
		m(2, 2) =  cp*ch;
		m(0, 3) = m(1, 3) = m(2, 3) = m(3, 0) = m(3, 1) = m(3, 2) = 0;
		m(3, 3) = 1;
		return m;
	}

	/**
	 * Gives matrix by applying consecutive rotations about X, Y, Z axis.
	 * @relates mat
	 */

	template <typename T, typename Traits> inline mat<T, 4, Traits>
		rotate4_xyz_matrix(const vec<T, 3, Traits> & xyz)
	{
		T s1 = 0, c1 = 1;
		if (xyz(0) != 0)
		{
			c1 = Traits::cos(xyz(0));
			s1 = Traits::sin(xyz(0));
		}
		T s2 = 0, c2 = 1;
		if (xyz(1) != 0)
		{
			c2 = Traits::cos(xyz(1));
			s2 = Traits::sin(xyz(1));
		}
		T s3 = 0, c3 = 1;
		if (xyz(2) != 0)
		{
			c3 = Traits::cos(xyz(2));
			s3 = Traits::sin(xyz(2));
		}

		mat<T, 4, Traits> m;
		m(0, 0) =  c3*c2;
		m(0, 1) = -s3*c1 + c3*s2*s1;
		m(0, 2) =  s3*s1 + c3*s2*c1;
		m(1, 0) =  s3*c2;
		m(1, 1) =  c3*c1 + s3*s2*s1;
		m(1, 2) = -c3*s1 + s3*s2*c1;
		m(2, 0) = -s2;
		m(2, 1) =  c2*s1;
		m(2, 2) =  c2*c1;
		m(0, 3) = m(1, 3) = m(2, 3) = m(3, 0) = m(3, 1) = m(3, 2) = 0;
		m(3, 3) = 1;
		return m;
	}

	/**
	 * Gives rotation matrix for given vector and angle.
	 * @relates mat
	 */

	template <typename T, typename Traits> inline mat<T, 3, Traits>
		rotate3_matrix(const vec<T, 3, Traits> & v, T a)
	{
		mat<T, 3, Traits> m;
		vec<T, 3, Traits> u = unit0(v);
		T s = Traits::sin(a), c = Traits::cos(a);
		T x = v[0], y = v[1], z = v[2];
		T xx = x * x, yy = y * y, zz = z * z;
		T xy = x * y, yz = y * z, zx = z * x;
		T xs = x * s, ys = y * s, zs = z * s;
		T one_c = 1 - c;
		m(0, 0) = (one_c * xx) + c;  m(0, 1) = (one_c * xy) - zs; m(0, 2) = (one_c * zx) + ys;
		m(1, 0) = (one_c * xy) + zs; m(1, 1) = (one_c * yy) + c;  m(1, 2) = (one_c * yz) - xs;
		m(2, 0) = (one_c * zx) - ys; m(2, 1) = (one_c * yz) + xs; m(2, 2) = (one_c * zz) + c;
		return m;
	}

	/**
	 * Gives rotation matrix for given vector and angle.
	 * @relates mat
	 */

	template <typename T, typename Traits> inline mat<T, 4, Traits>
		rotate4_matrix(const vec<T, 3, Traits> & v, T a)
	{
		mat<T, 4, Traits> m;
		vec<T, 3, Traits> u = unit0(v);
		T s = Traits::sin(a), c = Traits::cos(a);
		T x = u[0], y = u[1], z = u[2];
		T xx = x * x, yy = y * y, zz = z * z;
		T xy = x * y, yz = y * z, zx = z * x;
		T xs = x * s, ys = y * s, zs = z * s;
		T one_c = 1 - c;
		m(0, 0) = (one_c * xx) + c;  m(0, 1) = (one_c * xy) - zs; m(0, 2) = (one_c * zx) + ys; m(0, 3) = 0;
		m(1, 0) = (one_c * xy) + zs; m(1, 1) = (one_c * yy) + c;  m(1, 2) = (one_c * yz) - xs; m(1, 3) = 0;
		m(2, 0) = (one_c * zx) - ys; m(2, 1) = (one_c * yz) + xs; m(2, 2) = (one_c * zz) + c;  m(2, 3) = 0;
		m(3, 0) = 0;                 m(3, 1) = 0;                 m(3, 2) = 0;                 m(3, 3) = 1;
		return m;
	}

	template <typename T, typename Traits> inline mat<T, 4, Traits>
		frustum4_matrix(T left, T right, T bottom, T top, T znear, T zfar)
	{
		T dxinv = 1 / (right - left);
		T dyinv = 1 / (top - bottom);
		T dzinv = 1 / (zfar - znear);

		mat<T, 4, Traits> proj(mat<T, 4, Traits>::zero());
		proj(0, 0) = 2 * znear * dxinv;
		proj(1, 1) = 2 * znear * dyinv;
		proj(2, 2) = -(zfar + znear) * dzinv;
		proj(3, 3) = 0;
		proj(0, 2) = (right + left) * dxinv;
		proj(1, 2) = (top + bottom) * dyinv;
		proj(3, 2) = -1;
		proj(2, 3) = -2 * zfar * znear * dzinv;
		return proj;
	}

	template <typename T, typename Traits> inline mat<T, 4, Traits>
		perspective4_matrix(T fovy, T xaspect, T yaspect, T znear, T zfar)
	{
		T c = znear * Traits::tan(fovy / 2);
		T ymax =  c * yaspect;
		T ymin = -c * yaspect;
		T xmax =  c * xaspect;
		T xmin = -c * xaspect;
		return frustum4_matrix<T, Traits>(xmin, xmax, ymin, ymax, znear, zfar);
	}

	template <typename T, typename Traits> inline mat<T, 4, Traits>
		ortho4_matrix(T left, T right, T bottom, T top, T znear, T zfar)
	{
		T dxinv = 1 / (right - left);
		T dyinv = 1 / (top - bottom);
		T dzinv = 1 / (zfar - znear);

		mat<T, 4, Traits> proj(mat<T, 4, Traits>::zero());
		proj(0, 0) =  2 * dxinv;
		proj(1, 1) =  2 * dyinv;
		proj(2, 2) = -2 * dzinv;
		proj(3, 3) = 1;
		proj(0, 3) = -(right + left) * dxinv;
		proj(1, 3) = -(top + bottom) * dyinv;
		proj(2, 3) = -(zfar + znear) * dzinv;
		return proj;
	}

	template <typename T, typename Traits> inline mat<T, 4, Traits>
		lookat4_matrix(const vec<T, 3, Traits> & eye, const vec<T, 3, Traits> & center, const vec<T, 3, Traits> & up)
	{
		vec<T, 3, Traits> f = unit(center - eye);
		vec<T, 3, Traits> u = unit(vec<T, 3, Traits>(up));
		vec<T, 3, Traits> s = unit(vector_product(f, u));
		u = vector_product(s, f);

		mat<T, 4, Traits> m(mat<T, 4, Traits>::identity());
		m(0, 0) = s[0];
		m(0, 1) = s[1];
		m(0, 2) = s[2];
		m(1, 0) = u[0];
		m(1, 1) = u[1];
		m(1, 2) = u[2];
		m(2, 0) =-f[0];
		m(2, 1) =-f[1];
		m(2, 2) =-f[2];
		m(0, 3) =-dot_product(s, eye);
		m(1, 3) =-dot_product(u, eye);
		m(2, 3) = dot_product(f, eye);

		return m;
	}

	template <typename T, typename Traits> inline mat<T, 4, Traits>
		reflection4_matrix(const vec<T, 4, Traits> & plane)
	{
		mat<T, 4, Traits> m;
		T q = plane(0) * plane(0) + plane(1) * plane(1) + plane(2) * plane(2);

		m(0, 0) = q - 2 * plane(0) * plane(0);
		m(0, 1) = - 2 * plane(0) * plane(1);
		m(0, 2) = - 2 * plane(0) * plane(2);
		m(0, 3) = - 2 * plane(0) * plane(3);

		m(1, 0) = - 2 * plane(0) * plane(1);
		m(1, 1) = q - 2 * plane(1) * plane(1);
		m(1, 2) = - 2 * plane(1) * plane(2);
		m(1, 3) = - 2 * plane(1) * plane(3);

		m(2, 0) = - 2 * plane(0) * plane(2);
		m(2, 1) = - 2 * plane(1) * plane(2);
		m(2, 2) = q - 2 * plane(2) * plane(2);
		m(2, 3) = - 2 * plane(2) * plane(3);

		m(3, 0) = 0;
		m(3, 1) = 0;
		m(3, 2) = 0;
		m(3, 3) = q;

		return m;
	}

	/**
	 * Check if matrix produces rigid transform (or reflection).
	 * @relates mat
	 */

	template <typename T, size_t N, typename Traits> inline bool
		rigid_transform(const mat<T, 4, Traits> & m)
	{
		if (!(Traits::eq(m(3, 0), 0) && Traits::eq(m(3, 1), 0) && Traits::eq(m(3, 2), 0) && Traits::eq(m(3, 3), 0)))
			return false;
		mat<T, 4, Traits> n(inverse0(m));
		for (size_t i = 0; i < 3; i++)
		{
			for (size_t j = 0; j < 3; j++)
			{
				if (!Traits::eq(n(i, j), m(j, i)))
					return false;
			}
		}
		return true;
	}

	/**
	 * Transform vector by matrix.
	 * @relates vec
	 */

	template <typename T, size_t N, typename Traits> inline vec<T, N, Traits>
		transform(const vec<T, N, Traits> & v, const mat<T, N, Traits> & m)
	{
		vec<T, N, Traits> w;
		for (size_t i = 0; i < N; i++)
		{
			w(i) = 0;
			for (size_t j = 0; j < N; j++)
			{
				w(i) += m(i, j) * v(j);
			}
		}
		return w;
	}

	/**
	 * Transform point by matrix.
	 * @relates vec
	 */

	template <typename T, size_t N, typename Traits> inline vec<T, N, Traits>
		transform_point(const vec<T, N, Traits> & v, const mat<T, N+1, Traits> & m)
	{
		T s = m(N, N);
		for (size_t i = 0; i < N; i++)
		{
			s += m(N, i) * v(i);
		}
		T invs = 1 / s;
		vec<T, N, Traits> w;
		for (size_t i = 0; i < N; i++)
		{
			T t = m(i, N);
			for (size_t j = 0; j < N; j++)
			{
				t += m(i, j) * v(j);
			}
			w(i) = t * invs;
		}
		return w;
	}

	/**
	 * Transform vector by matrix.
	 * @relates vec
	 */

	template <typename T, size_t N, typename Traits> inline vec<T, N, Traits>
		transform_vector(const vec<T, N, Traits> & v, const mat<T, N+1, Traits> & m)
	{
		vec<T, N, Traits> w;
		for (size_t i = 0; i < N; i++)
		{
			w(i) = 0;
			for (size_t j = 0; j < N; j++)
			{
				w(i) += m(i, j) * v(j);
			}
		}
		return w;
	}

	/**
	 * Calculates MxM subdeterminant of NxN matrix with given disabled rows
	 * and columns.
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> inline T
		fast_subdet(const mat<T, N, Traits> & m, size_t n)
	{
		assert(n < 4);
		switch (n)
		{
		case 1:
			return (m(0, 0));
		case 2:
			return (m(0, 0) * m(1, 1)) -
			       (m(0, 1) * m(1, 0));
		case 3:
			return (m(0, 0) * m(1, 1) * m(2, 2) + m(0, 1) * m(1, 2) * m(2, 0) + m(0, 2) * m(1, 0) * m(2, 1)) -
			       (m(0, 2) * m(1, 1) * m(2, 0) + m(0, 1) * m(1, 0) * m(2, 2) + m(0, 0) * m(1, 2) * m(2, 1));
		}
		return 1;
	}

	template <typename T, size_t N, typename Traits> T
		subdeterminant(const mat<T, N, Traits> & m, size_t n)
	{
		if (n < 4)
			return fast_subdet(m, n);
		
		mat<T, N, Traits> ms;
		for (size_t i = 1; i < n; i++)
		{
			for (size_t j = 1; j < n; j++)
			{
				ms(i - 1, j - 1) = m(i, j);
			}
		}
		T det = m(0, 0) * subdeterminant(ms, n - 1);
		T sign = 1;
		for (size_t s = 1; s < n; s++)
		{
			sign = -sign;
			for (size_t t = 1; t < n; t++)
			{
				ms(s - 1, t - 1) = m(s - 1, t);
			}
			det += m(s, 0) * subdeterminant(ms, n - 1) * sign;
		}
		return det;
	}
	
	/**
	 * Calculates determinant of NxN matrix.
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> inline T
		determinant(const mat<T, N, Traits> & m)
	{
		return subdeterminant(m, N);
	}
	
	/**
	 * Transposes NxN matrix.
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> mat<T, N, Traits>
		transpose(const mat<T, N, Traits> & m)
	{
		mat<T, N, Traits> mt;
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				mt(j, i) = m(i, j);
			}
		}
		return mt;
	}
	
	/**
	 * Calculates inversion of NxN matrix M. Assumes that det(M) != 0.
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> mat<T, N, Traits>
		inverse(const mat<T, N, Traits> & m)
	{
		T det = determinant(m), invdet;
		if (Traits::eq(det, 0))
			invdet = Traits::infinity();
		else
			invdet = 1 / det;
		
		mat<T, N, Traits> mi;
		for (size_t i = 0; i < N; i++)
		{
			mat<T, N, Traits> ms;
			for (size_t k = 0, r = 0; k < N; k++)
			{
				if (k == i)
					continue;
				for (size_t l = 1; l < N; l++)
				{
					ms(r, l - 1) = m(k, l);
				}
				r++;
			}
			T sign = (T) (1 - ((int) (i % 2) * 2));
			mi(0, i) = subdeterminant(ms, N - 1) * sign * invdet;
			for (size_t j = 1; j < N; j++)
			{
				sign = -sign;
				for (size_t k = 0, r = 0; k < N; k++)
				{
					if (k == i)
						continue;
					ms(r, j - 1) = m(k, j - 1);
					r++;
				}
				mi(j, i) = subdeterminant(ms, N - 1) * sign * invdet;
			}
		}
		return mi;
	}
	
	/**
	 * Calculates inversion of NxN matrix M. If det(M) = 0, then returns zero matrix.
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> inline mat<T, N, Traits>
		inverse0(const mat<T, N, Traits> & m)
	{
		T det = determinant(m);
		if (Traits::eq(det, 0))
			return mat<T, N, Traits>::zero();
		return inverse(m);
	}
	
	/**
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> bool
		operator == (const mat<T, N, Traits> & m1, const mat<T, N, Traits> & m2)
	{
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				if (!Traits::eq(m1(i, j), m2(i, j)))
					return false;
			}
		}
		return true;
	}
	
	/**
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> inline bool
		operator != (const mat<T, N, Traits> & m1, const mat<T, N, Traits> & m2)
	{
		return !(m1 == m2);
	}
	
	/**
	 * Intended for containers only!
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> bool
		operator < (const mat<T, N, Traits> & m1, const mat<T, N, Traits> & m2)
	{
		for (size_t i = 0; i < N; i++)
		{
			for (size_t j = 0; j < N; j++)
			{
				if (m1(i, j) < m2(i, j))
					return true;
				if (m2(i, j) < m1(i, j))
					return false;
			}
		}
		return false;
	}

	/**
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> inline mat<T, N, Traits>
		operator + (const mat<T, N, Traits> & m1, const mat<T, N, Traits> & m2)
	{
		mat<T, N, Traits> ms(m1);
		return ms += m2;
	}
	
	/**
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> inline mat<T, N, Traits>
		operator - (const mat<T, N, Traits> & m1, const mat<T, N, Traits> & m2)
	{
		mat<T, N, Traits> md(m1);
		return md -= m2;
	}
	
	/**
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> inline mat<T, N, Traits>
		operator * (const mat<T, N, Traits> & m, T s)
	{
		mat<T, N, Traits> mp(m);
		return mp *= s;
	}

	/**
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> inline mat<T, N, Traits>
		operator * (const mat<T, N, Traits> & m1, const mat<T, N, Traits> & m2)
	{
		mat<T, N, Traits> mp(m1);
		return mp *= m2;
	}

	/**
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits> mat<T, N, Traits> 
		operator / (const mat<T, N, Traits> & m1, const mat<T, N, Traits> & m2)
	{
		mat<T, N, Traits> md(m1);
		return md /= m2;
	}
	
	/**
	 * Reads matrix from stream. Assumes following format: [(x11,...,x1M),...,(xN1,...,xNM)].
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits, typename CharT, typename CharTraits> std::basic_istream<CharT, CharTraits> &
		operator >> (std::basic_istream<CharT, CharTraits> & is, mat<T, N, Traits> & m)
	{
		CharT ch;
		is >> ch;
		if (ch == '[')
		{
			size_t i = 0;
			do
			{
				if (i >= N)
					break;
				vec<T, N, Traits> v;
				is >> v;
				for (size_t j = 0; j < N; j++)
				{
					m(i, j) = v(j);
				}
				is >> ch;
			} while (ch == ',');
			if (ch != ']')
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
	 * Writes matrix to stream. Uses following format: [(x11,...,x1M),...,(xN1,...,xNM)].
	 * @relates mat
	 */
	
	template <typename T, size_t N, typename Traits, typename CharT, typename CharTraits> std::basic_ostream<CharT, CharTraits> &
		operator << (std::basic_ostream<CharT, CharTraits> & os, const mat<T, N, Traits> & m)
	{
		os << '[';
		for (size_t i = 0; i < N; i++)
		{
			if (i > 0)
			{
				os << ',';
			}
			vec<T, N, Traits> v;
			for (size_t j = 0; j < N; j++)
			{
				v(j) = m(i, j);
			}
			os << v;
		}
		os << ']';
		return os;
	}
	
	/**
	 * Matrix instances for 2D, 3D and 4D cases.
	 */
	
	template <typename T, typename Traits = float_traits<T> >
		class mat2x2 : public mat<T, 2, Traits>
	{
		
	public:
		
		inline mat2x2()
		{
#ifdef CGLIB_CLEAR
			clear();
#endif
		}
		inline mat2x2(const mat<T, 2, Traits> & v) : mat<T, 2, Traits>(v) { }
	};
	
	template <typename T, typename Traits = float_traits<T> >
		class mat3x3 : public mat<T, 3, Traits>
	{
		
	public:
		
		inline mat3x3()
		{
#ifdef CGLIB_CLEAR
			clear();
#endif
		}
		inline mat3x3(const mat<T, 3, Traits> & v) : mat<T, 3, Traits>(v) { }
	};
	
	template <typename T, typename Traits = float_traits<T> >
		class mat4x4 : public mat<T, 4, Traits>
	{
		
	public:
		
		inline mat4x4()
		{
#ifdef CGLIB_CLEAR
			clear();
#endif
		}
		inline mat4x4(const mat<T, 4, Traits> & v) : mat<T, 4, Traits>(v) { }
	};
	
}

#endif
