/*
* Copyright 2014 Nutiteq Llc. All rights reserved.
* Copying and using this code is allowed only according
* to license terms, as given in https://www.nutiteq.com/license/
*/

#ifndef _NUTI_VT_STROKESET_H_
#define _NUTI_VT_STROKESET_H_

#include "Bitmap.h"

#include <memory>
#include <mutex>
#include <unordered_map>

namespace Nuti { namespace VT {
	class StrokeSet {
	public:
		using StrokeId = unsigned int;
		
		struct Stroke {
			StrokeId strokeId;
			float scale;
			int y0;
			int y1;

			Stroke(StrokeId strokeId, float scale, int y0, int y1) : strokeId(strokeId), scale(scale), y0(y0), y1(y1) { }
		};

		explicit StrokeSet(int width);
		virtual ~StrokeSet() = default;

		int getWidth() const;
		const std::unique_ptr<Stroke>& getStroke(StrokeId code) const;
		StrokeId loadBitmapPattern(const std::shared_ptr<BitmapPattern>& bitmapPattern);
		std::shared_ptr<BitmapPattern> getBitmapPattern() const;

	private:
		int _width;
		int _height;
		std::unordered_map<StrokeId, std::unique_ptr<Stroke>> _strokeMap;
		std::unordered_map<std::shared_ptr<BitmapPattern>, StrokeId> _bitmapStrokeMap;
		std::shared_ptr<BitmapPattern> _bitmapPattern;
		mutable std::mutex _mutex;
	};
} }

#endif
