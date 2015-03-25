/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_BITMAPMANAGER_H_
#define _NUTI_VT_BITMAPMANAGER_H_

#include "Bitmap.h"

#include <memory>
#include <string>
#include <map>
#include <mutex>

namespace Nuti { namespace VT {
	class BitmapManager {
	public:
		class BitmapLoader {
		public:
			virtual ~BitmapLoader() = default;

			virtual std::shared_ptr<Bitmap> load(const std::string& fileName) const = 0;
		};

		BitmapManager(const std::shared_ptr<BitmapLoader>& loader);
		~BitmapManager();

		std::shared_ptr<Bitmap> getBitmap(const std::string& fileName) const;
		std::shared_ptr<Bitmap> loadBitmap(const std::string& fileName);
		void storeBitmap(const std::string& fileName, const std::shared_ptr<Bitmap>& bitmap);

		std::shared_ptr<BitmapPattern> getBitmapPattern(const std::string& fileName) const;
		std::shared_ptr<BitmapPattern> loadBitmapPattern(const std::string& fileName, float widthScale, float heightScale);
		void storeBitmapPattern(const std::string& fileName, const std::shared_ptr<BitmapPattern>& bitmapPattern);

		static std::shared_ptr<const Bitmap> scale(const std::shared_ptr<const Bitmap>& bitmap, int width, int height);
		static std::shared_ptr<const Bitmap> scaleToPOT(const std::shared_ptr<const Bitmap>& bitmap);

	protected:
		std::shared_ptr<BitmapLoader> _bitmapLoader;
		std::map<std::string, std::shared_ptr<Bitmap>> _bitmapMap;
		std::map<std::string, std::shared_ptr<BitmapPattern>> _bitmapPatternMap;

		mutable std::mutex _mutex;
	};
} }

#endif