#ifndef cglib_frustum3_h

#define cglib_frustum3_h

#include "vec.h"
#include "bbox.h"

namespace cglib
{

	/**
	 * N-dimensional bounding box
	 */

	template <typename T, typename Traits = float_traits<T> >
		class frustum3
	{

	public:

		typedef T value_type;
		typedef Traits traits_type;
		typedef vec<T, 3, Traits> point_type;
		typedef vec<T, 4, Traits> plane_type;
		typedef bounding_box<T, 3, Traits> bbox_type;

		plane_type planes[6];

		inline frustum3() { clear(); }

		void clear()
		{
			for (size_t i = 0; i < 6; i++)
			{
				planes[i].clear();
			}
		}

		point_type extreme_point(size_t i1, size_t i2, size_t i3) const
		{
			typedef vec<T, 4, Traits> vector4_type;

			T d = dot_product(planes[i1], vector_product(planes[i2], planes[i3]));
			vector4_type v1 = vector_product(planes[i2], planes[i3]) * planes[i1](3);
			vector4_type v2 = vector_product(planes[i3], planes[i1]) * planes[i2](3);
			vector4_type v3 = vector_product(planes[i1], planes[i2]) * planes[i3](3);
			return proj_o(v1 + v2 + v3) * (-1 / d);
		}

		bbox_type boundingbox() const
		{               
			T extreme = traits_type::infinity();
			point_type min(extreme, extreme, extreme);
			point_type max(-extreme, -extreme, -extreme);
			for (int i = 0; i < 8; i++)
			{
				size_t idxs[3];
				idxs[0] = i & 1 ? 4 : 5;
				idxs[1] = i & 2 ? 2 : 3;
				idxs[2] = i & 4 ? 0 : 1;
				point_type point = extreme_point(idxs[0], idxs[1], idxs[2]);
				for (int j = 0; j < 3; j++)
				{
					min(j) = std::min(min(j), point(j));
					max(j) = std::max(max(j), point(j));
				}
			}
			return bbox_type(min, max);
		}

		bool inside(const point_type & point) const
		{
			for (int p = 0; p < 6; p++)
			{
				T d = plane_distance(p, point);
				if (d <= 0)
					return false;
			}
			return true;
		}

		bool inside(const plane_type & plane, T side) const
		{
			for (int i = 0; i < 8; i++)
			{
				size_t idxs[3];
				idxs[0] = i & 1 ? 4 : 5;
				idxs[1] = i & 2 ? 2 : 3;
				idxs[2] = i & 4 ? 0 : 1;
				T d = plane_distance(plane, extreme_point(idxs[0], idxs[1], idxs[2]));
				if (d * side > 0)
					return true;
			}
		}

		bool inside(const bbox_type & bbox) const
		{
			for (int p = 0; p < 6; p++)
			{
				int i;
				for (i = 0; i < 8; i++)
				{
					point_type point;
					point(0) = i & 1 ? bbox.min(0) : bbox.max(0);
					point(1) = i & 2 ? bbox.min(1) : bbox.max(1);
					point(2) = i & 4 ? bbox.min(2) : bbox.max(2);
					T d = plane_distance(p, point);
					if (d > 0)
						break;
				}
				if (i == 8)
					return false;
			}
			return true;
		}

		T distance(const point_type & point) const
		{
			T max_d = -traits_type::infinity();
			for (int p = 0; p < 6; p++)
			{
				T d = -plane_distance(p, point) / length(proj_o(planes[p]));
				max_d = std::max(max_d, d);
			}
			return max_d;
		}

		T plane_distance(size_t i, const point_type & point) const
		{
			return dot_product(planes[i], expand(point, (T) 1));
		}

		frustum3<T, Traits> & intersect(const frustum3<T, Traits> & fru)
		{
			for (int p1 = 0; p1 < 6; p1++)
			{
				for (int p2 = 0; p2 < 6; p2++)
				{
					if (dot_product(proj_o(planes[p2]), proj_o(fru.planes[p1])) <= 0)
						continue;
					plane_type pl = planes[p2];
					planes[p2] = fru.planes[p1];
					if (inside(pl))
						break;
					planes[p2] = pl;
				}
			}
			return *this;
		}

		template <typename S, typename TraitsS>
			static frustum3<T, Traits> convert(const frustum3<S, TraitsS> & fru)
		{
			frustum3<T, Traits> fru2;
			for (int p = 0; p < 6; p++)
			{
				fru2.plane[p] = plane_type::convert(fru.plane[p]);
			}
			return fru2;
		}
	};

	/**
	 * Operators
	 */

	template <typename T, typename Traits> inline
		bool operator == (const frustum3<T, Traits> & fru1, const frustum3<T, Traits> & fru2)
	{
		for (size_t i = 0; i < 6; i++)
		{
			if (fru1.planes[i] != fru2.planes[i])
				return false;
		}
		return true;
	}

	template <typename T, typename Traits> inline
		bool operator != (const frustum3<T, Traits> & fru1, const frustum3<T, Traits> & fru2)
	{
		return !(fru1 == fru2);
	}

	template <typename T, typename Traits>
		frustum3<T, Traits> ortho_frustum(T left, T right, T bottom, T top, T znear, T zfar)
	{
		typedef vec4<T, Traits> plane_type;

		frustum3<T, Traits> fru;
		fru.planes[0] = plane_type( 0,  0, -1, -znear); // z-axis is negated
		fru.planes[1] = plane_type( 0,  0,  1,  zfar);
		fru.planes[2] = plane_type( 0,  1,  0,  left);
		fru.planes[3] = plane_type( 0, -1,  0, -right);
		fru.planes[4] = plane_type( 1,  0,  0,  bottom);
		fru.planes[5] = plane_type(-1,  0,  0, -top);
		return fru;
	}

	template <typename T, typename Traits>
		frustum3<T, Traits> perspective_frustum(T fovy, T xaspect, T yaspect, T znear, T zfar)
	{
		typedef vec4<T, Traits> plane_type;

		T s = Traits::sin(fovy / 2), c = Traits::cos(fovy / 2);
		frustum3<T, Traits> fru;
		fru.planes[5] = plane_type( c,  0, -s * xaspect, 0);
		fru.planes[4] = plane_type(-c,  0, -s * xaspect, 0);
		fru.planes[3] = plane_type( 0,  c, -s * yaspect, 0);
		fru.planes[2] = plane_type( 0, -c, -s * yaspect, 0);
		fru.planes[1] = plane_type( 0,  0,  1,  zfar);  // z-axis is negated
		fru.planes[0] = plane_type( 0,  0, -1, -znear);
		return fru;
	}

	template <typename T, typename Traits>
		frustum3<T, Traits> gl_projection_frustum(const mat<T, 4, Traits> & m)
	{
		typedef vec4<T, Traits> plane_type;

		frustum3<T, Traits> fru;
		fru.planes[5] = plane_type(m(3, 0) + m(0, 0), m(3, 1) + m(0, 1), m(3, 2) + m(0, 2), m(3, 3) + m(0, 3));
		fru.planes[4] = plane_type(m(3, 0) - m(0, 0), m(3, 1) - m(0, 1), m(3, 2) - m(0, 2), m(3, 3) - m(0, 3));
		fru.planes[3] = plane_type(m(3, 0) + m(1, 0), m(3, 1) + m(1, 1), m(3, 2) + m(1, 2), m(3, 3) + m(1, 3));
		fru.planes[2] = plane_type(m(3, 0) - m(1, 0), m(3, 1) - m(1, 1), m(3, 2) - m(1, 2), m(3, 3) - m(1, 3));
		fru.planes[1] = plane_type(m(3, 0) + m(2, 0), m(3, 1) + m(2, 1), m(3, 2) + m(2, 2), m(3, 3) + m(2, 3));
		fru.planes[0] = plane_type(m(3, 0) - m(2, 0), m(3, 1) - m(2, 1), m(3, 2) - m(2, 2), m(3, 3) - m(2, 3));
		return fru;
	}

	template <typename T, typename Traits>
		frustum3<T, Traits> bbox_frustum(const bounding_box<T, 3, Traits> & bbox)
	{
		typedef vec4<T, Traits> plane_type;

		frustum3<T, Traits> fru;
		fru.planes[0] = plane_type( 0,  0,  1, -bbox.min(2));
		fru.planes[1] = plane_type( 0,  0, -1,  bbox.max(2));
		fru.planes[2] = plane_type( 0,  1,  0, -bbox.min(1));
		fru.planes[3] = plane_type( 0, -1,  0,  bbox.max(1));
		fru.planes[4] = plane_type( 1,  0,  0, -bbox.min(0));
		fru.planes[5] = plane_type(-1,  0,  0,  bbox.max(0));
		return fru;
	}

	template <typename T, typename Traits>
		frustum3<T, Traits> transform_frustum(const frustum3<T, Traits> & fru, const mat<T, 4, Traits> & m)
	{
		mat<T, 4, Traits> inv_trans_m = transpose(inverse(m));
		frustum3<T, Traits> fru2;
		for (int p = 0; p < 6; p++)
		{
			fru2.planes[p] = transform(fru.planes[p], inv_trans_m);
		}
		return fru2;
	}

	template <typename T, typename Traits>
		frustum3<T, Traits> intersect(const frustum3<T, Traits> & fru1, const frustum3<T, Traits> & fru2)
	{
		frustum3<T, Traits> fru3(fru1);
		return fru3.intersect(fru2);
	}

	/**
	 * Reads frustum info from stream.
	 * @relates frustum3
	 */
	
	template <typename T, typename Traits, typename CharT, typename CharTraits> std::basic_istream<CharT, CharTraits> &
		operator >> (std::basic_istream<CharT, CharTraits> & is, frustum3<T, Traits> & fru)
	{
		for (size_t i = 0; i < 6; i++)
		{
			if (i != 0)
			{
				CharT ch;
				is >> ch;
				if (ch != ',')
				{
					is.setstate(std::ios_base::failbit);
					return is;
				}
			}
			is >> fru.planes[i];
		}
		return is;
	}
	
	/**
	 * Writes frustum info to stream.
	 * @relates frustum3
	 */
	
	template <typename T, typename Traits, typename CharT, typename CharTraits> std::basic_ostream<CharT, CharTraits> &
		operator << (std::basic_ostream<CharT, CharTraits> & os, const frustum3<T, Traits> & fru)
	{
		for (size_t i = 0; i < 6; i++)
		{
			if (i != 0)
				os << ',';
			os << fru.planes[i];
		}
		return os;
	}

}

#endif
