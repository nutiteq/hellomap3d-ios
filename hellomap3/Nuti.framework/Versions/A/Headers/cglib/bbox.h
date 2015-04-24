#ifndef cglib_bbox_h

#define cglib_bbox_h

#include "vec.h"
#include "mat.h"

// Hack-fix for Win32
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

namespace cglib
{

	/**
	 * N-dimensional bounding box
	 */

	template <typename T, size_t N, typename Traits = float_traits<T> >
		class bounding_box
	{

	public:

		typedef T value_type;
		typedef Traits traits_type;
		typedef vec<T, N, Traits> point_type;

		point_type min, max; // represents set [min..max]

		bounding_box() { clear(); }
		explicit bounding_box(const point_type & p) : min(p), max(p) { }
		bounding_box(const point_type & min, const point_type & max) : min(min), max(max) { }

		void clear()
		{
			T val = traits_type::infinity();
			for (size_t i = 0; i < N; i++)
			{
				min(i) = val;
				max(i) = -val;
			}
		}

		void create_largest()
		{
			T val = traits_type::infinity();
			for (size_t i = 0; i < N; i++)
			{
				min(i) = -val;
				max(i) = val;
			}
		}

		bool empty() const
		{
			for (size_t i = 0; i < N; i++)
			{
				if (min(i) >= max(i))
					return true;
			}
			return false;
		}

		T product() const
		{
			T p = 1;
			point_type s = size();
			for (size_t i = 0; i < N; i++)
			{
				p *= s(i);
			}
			return p;
		}

		point_type size() const
		{
			return max - min;
		}

		bool inside(const point_type & point) const
		{
			for (int i = 0; i < N; i++)
			{
				if (min(i) > point(i) || max(i) < point(i))
					return false;
			}
			return true;
		}
	
		bool inside(const bounding_box<T, N, Traits> & b) const
		{
			for (size_t i = 0; i < N; i++)
			{
				if (min(i) > b.max(i) || max(i) < b.min(i))
					return false;
			}
			return true;
		}

		point_type nearest_point(const point_type & point) const
		{
			point_type point_nearest = point;
			for (int i = 0; i < N; i++)
			{
				if (min(i) > point(i))
					point_nearest(i) = min(i);
				else if (max(i) < point(i))
					point_nearest(i) = max(i);
			}
			return point_nearest;
		}

		bounding_box<T, N, Traits> & operator += (const point_type & offset)
		{
			min += offset;
			max += offset;
			return *this;
		}

		bounding_box<T, N, Traits> & operator -= (const point_type & offset)
		{
			min -= offset;
			max -= offset;
			return *this;
		}

		bounding_box<T, N, Traits> & add(const point_type & point)
		{
			for (size_t i = 0; i < N; i++)
			{
				min(i) = std::min(min(i), point(i));
				max(i) = std::max(max(i), point(i));
			}
			return *this;
		}

		bounding_box<T, N, Traits> & add(const bounding_box<T, N, Traits> & b)
		{
			for (size_t i = 0; i < N; i++)
			{
				min(i) = std::min(min(i), b.min(i));
				max(i) = std::max(max(i), b.max(i));
			}
			return *this;
		}

		template <typename It>
			bounding_box<T, N, Traits> & add(It begin, It end)
		{
			for (It it = begin; it != end; it++)
			{
				add(*it);
			}
			return *this;
		}

		bounding_box<T, N, Traits> & intersect(const bounding_box<T, N, Traits> & b)
		{
			for (size_t i = 0; i < N; i++)
			{
				min(i) = std::max(min(i), b.min(i));
				max(i) = std::min(max(i), b.max(i));
			}
			if (empty())
				clear(); // this will ensure that further 'add' operations behave as expected
			return *this;
		}

		template <typename S, typename TraitsS>
			static bounding_box<T, N, Traits> convert(const bounding_box<S, N, TraitsS> & b)
		{
			return bounding_box<T, N, Traits>(point_type::convert(b.min), point_type::convert(b.max));
		}
	};

	/**
	 * Operators
	 */

	template <typename T, size_t N, typename Traits> inline
		bool operator == (const bounding_box<T, N, Traits> & b1, const bounding_box<T, N, Traits> & b2)
	{
		return b1.min == b2.min && b1.max == b2.max;
	}

	template <typename T, size_t N, typename Traits> inline
		bool operator != (const bounding_box<T, N, Traits> & b1, const bounding_box<T, N, Traits> & b2)
	{
		return !(b1 == b2);
	}

	template <typename T, size_t N, typename Traits> inline
		bounding_box<T, N, Traits> operator + (const bounding_box<T, N, Traits> & b1, const typename bounding_box<T, N, Traits>::point_type & p)
	{
		bounding_box<T, N, Traits> b2(b1);
		return b2 += p;
	}

	template <typename T, size_t N, typename Traits> inline
		bounding_box<T, N, Traits> operator - (const bounding_box<T, N, Traits> & b1, const typename bounding_box<T, N, Traits>::point_type & p)
	{
		bounding_box<T, N, Traits> b2(b1);
		return b2 -= p;
	}

	template <typename T, size_t N, typename Traits>
		bounding_box<T, N, Traits> transform_bbox(const bounding_box<T, N, Traits> & bbox, const mat<T, N+1, Traits> & m)
	{
		bounding_box<T, N, Traits> bbox_trans;
		for (size_t i = 0; i < (1 << N); i++)
		{
			vec<T, N, Traits> p;
			for (size_t j = 0; j < N; j++)
			{
				p(j) = ((i >> j) & 1) != 0 ? bbox.max(j) : bbox.min(j);
			}
			vec<T, N, Traits> p_trans = transform_point(p, m);
			bbox_trans.add(p_trans);
		}
		return bbox_trans;
	}

	template <typename T, size_t N, typename Traits>
		bounding_box<T, N, Traits> add(const bounding_box<T, N, Traits> & b1, const bounding_box<T, N, Traits> & b2)
	{
		bounding_box<T, N, Traits> b3(b1);
		return b3.add(b2);
	}

	template <typename T, size_t N, typename Traits>
		bounding_box<T, N, Traits> intersect(const bounding_box<T, N, Traits> & b1, const bounding_box<T, N, Traits> & b2)
	{
		bounding_box<T, N, Traits> b3(b1);
		return b3.intersect(b2);
	}


	/**
	 * Reads bounding box from stream.
	 * @relates bounding_box
	 */
	
	template <typename T, size_t N, typename Traits, typename CharT, typename CharTraits> std::basic_istream<CharT, CharTraits> &
		operator >> (std::basic_istream<CharT, CharTraits> & is, bounding_box<T, N, Traits> & b)
	{
		is >> b.min;
		CharT ch;
		is >> ch;
		if (ch != ',')
		{
			is.setstate(std::ios_base::failbit);
			return is;
		}
		is >> b.max;
		return is;
	}
	
	/**
	 * Writes bounding box info to stream.
	 * @relates bounding_box
	 */
	
	template <typename T, size_t N, typename Traits, typename CharT, typename CharTraits> std::basic_ostream<CharT, CharTraits> &
		operator << (std::basic_ostream<CharT, CharTraits> & os, const bounding_box<T, N, Traits> & b)
	{
		os << b.min << ',' << b.max;
		return os;
	}
	
}

#endif
