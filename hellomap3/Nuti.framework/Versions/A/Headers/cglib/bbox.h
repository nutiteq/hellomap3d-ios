#ifndef _CGLIB_BBOX_H
#define _CGLIB_BBOX_H

#include "vec.h"
#include "mat.h"

#include <algorithm>
#include <utility>

namespace cglib
{

	/**
	 * N-dimensional bounding box
	 */

	template <typename T, size_t N, typename Traits = float_traits<T> >
		class bbox
	{

	public:

		typedef T value_type;
		typedef Traits traits_type;
		typedef vec<T, N, Traits> point_type;

		inline bbox() = default;
		
		inline explicit bbox(const point_type & point) : min(point), max(point) { }
		
		inline explicit bbox(const point_type & min, const point_type & max) : min(min), max(max) { }

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
			vec<T, N, Traits> v = size();
			T p = 1;
			for_each_unrolled<N>([&](size_t i)
			{
				p *= v(i);
			});
			return p;
		}

		vec<T, N, Traits> size() const
		{
			vec<T, N, Traits> v;
			for_each_unrolled<N>([&](size_t i)
			{
				v(i) = std::max(static_cast<T>(0), max(i) - min(i));
			});
			return v;
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
	
		bool inside(const bbox<T, N, Traits> & b) const
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
			for_each_unrolled<N>([&](size_t i)
			{
				if (min(i) > point(i))
					point_nearest(i) = min(i);
				else if (max(i) < point(i))
					point_nearest(i) = max(i);
			});
			return point_nearest;
		}

		bbox<T, N, Traits> & add(const point_type & point)
		{
			for_each_unrolled<N>([&](size_t i)
			{
				min(i) = std::min(min(i), point(i));
				max(i) = std::max(max(i), point(i));
			});
			return *this;
		}

		bbox<T, N, Traits> & add(const bbox<T, N, Traits> & b)
		{
			for_each_unrolled<N>([&](size_t i)
			{
				min(i) = std::min(min(i), b.min(i));
				max(i) = std::max(max(i), b.max(i));
			});
			return *this;
		}

		template <typename It>
			bbox<T, N, Traits> & add(It begin, It end)
		{
			for (It it = begin; it != end; it++)
			{
				add(*it);
			}
			return *this;
		}

		bbox<T, N, Traits> & intersect(const bbox<T, N, Traits> & b)
		{
			for_each_unrolled<N>([&](size_t i)
			{
				min(i) = std::max(min(i), b.min(i));
				max(i) = std::min(max(i), b.max(i));
			});
			if (empty())
				*this = smallest(); // this will ensure that further 'add' operations behave as expected
			return *this;
		}

		void clear()
		{
			min.clear();
			max.clear();
		}
		
		void swap(bbox<T, N, Traits> & b)
		{
			min.swap(b.min);
			max.swap(b.max);
		}

		inline static bbox<T, N, Traits> smallest()
		{
			T val = traits_type::infinity();
			vec<T, N, Traits> min, max;
			for_each_unrolled<N>([&](size_t i)
			{
				min(i) = val;
				max(i) = -val;
			});
			return bbox<T, N, Traits>(min, max);
		}
		
		inline static bbox<T, N, Traits> largest()
		{
			T val = traits_type::infinity();
			vec<T, N, Traits> min, max;
			for_each_unrolled<N>([&](size_t i)
			{
				min(i) = -val;
				max(i) = val;
			});
			return bbox<T, N, Traits>(min, max);
		}

        template <typename It>
            static bbox<T, N, Traits> make_union(It begin, It end)
        {
            bbox<T, N, Traits> b = bbox<T, N, Traits>::smallest();
            std::for_each(begin, end, [&b](const typename bbox<T, N, Traits>::point_type & p) { b.add(p); });
            return b;
        }
		
		template <typename S, typename TraitsS>
			static bbox<T, N, Traits> convert(const bbox<S, N, TraitsS> & b)
		{
			return bbox<T, N, Traits>(point_type::convert(b.min), point_type::convert(b.max));
		}
		
	public:

		point_type min, max; // represents set [min..max]
	};

	/**
	 * Operators
	 */

	template <typename T, size_t N, typename Traits> inline
		bool operator == (const bbox<T, N, Traits> & b1, const bbox<T, N, Traits> & b2)
	{
		return b1.min == b2.min && b1.max == b2.max;
	}

	template <typename T, size_t N, typename Traits> inline
		bool operator != (const bbox<T, N, Traits> & b1, const bbox<T, N, Traits> & b2)
	{
		return !(b1 == b2);
	}

	template <typename T, size_t N, typename Traits> inline
		bbox<T, N, Traits> operator + (const bbox<T, N, Traits> & b1, const typename bbox<T, N, Traits>::point_type & p)
	{
		bbox<T, N, Traits> b2(b1);
		return b2 += p;
	}

	template <typename T, size_t N, typename Traits> inline
		bbox<T, N, Traits> operator - (const bbox<T, N, Traits> & b1, const typename bbox<T, N, Traits>::point_type & p)
	{
		bbox<T, N, Traits> b2(b1);
		return b2 -= p;
	}

	template <typename T, size_t N, typename Traits>
		bbox<T, N, Traits> transform_bbox(const bbox<T, N, Traits> & b, const mat<T, N+1, Traits> & m)
	{
		bbox<T, N, Traits> b_trans = bbox<T, N, Traits>::smallest();
		for (size_t i = 0; i < (1 << N); i++)
		{
			vec<T, N, Traits> p;
			for_each_unrolled<N>([&](size_t j)
			{
				p(j) = ((i >> j) & 1) != 0 ? b.max(j) : b.min(j);
			});
			vec<T, N, Traits> p_trans = transform_point(p, m);
			b_trans.add(p_trans);
		}
		return b_trans;
	}

	template <typename T, size_t N, typename Traits>
		bbox<T, N, Traits> add(const bbox<T, N, Traits> & b1, const bbox<T, N, Traits> & b2)
	{
		bbox<T, N, Traits> b3(b1);
		return b3.add(b2);
	}

	template <typename T, size_t N, typename Traits>
		bbox<T, N, Traits> intersect(const bbox<T, N, Traits> & b1, const bbox<T, N, Traits> & b2)
	{
		bbox<T, N, Traits> b3(b1);
		return b3.intersect(b2);
	}

	/**
	 * Reads bounding box from stream.
	 * @relates bbox
	 */
	
	template <typename T, size_t N, typename Traits, typename CharT, typename CharTraits> std::basic_istream<CharT, CharTraits> &
		operator >> (std::basic_istream<CharT, CharTraits> & is, bbox<T, N, Traits> & b)
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
	 * @relates bbox
	 */
	
	template <typename T, size_t N, typename Traits, typename CharT, typename CharTraits> std::basic_ostream<CharT, CharTraits> &
		operator << (std::basic_ostream<CharT, CharTraits> & os, const bbox<T, N, Traits> & b)
	{
		os << b.min << ',' << b.max;
		return os;
	}
	
	/**
	 * Commonly used instances for 2D, 3D and 4D cases
	 */
	
	template <typename T, typename Traits = float_traits<T> > using bbox2 = bbox<T, 2, Traits>;
	template <typename T, typename Traits = float_traits<T> > using bbox3 = bbox<T, 3, Traits>;
	template <typename T, typename Traits = float_traits<T> > using bbox4 = bbox<T, 4, Traits>;

}

#endif
