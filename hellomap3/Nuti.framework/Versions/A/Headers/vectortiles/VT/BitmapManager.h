#pragma once

#include "Bitmap.h"

#include <memory>
#include <string>
#include <map>
#include <mutex>

namespace Nuti {
	namespace VT {
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

			static std::shared_ptr<const Bitmap> scaleToPOT(const std::shared_ptr<const Bitmap>& bitmap);

		protected:
			std::shared_ptr<BitmapLoader> _bitmapLoader;
			std::map<std::string, std::shared_ptr<Bitmap>> _bitmapMap;
			std::map<std::string, std::shared_ptr<BitmapPattern>> _bitmapPatternMap;

			mutable std::mutex _mutex;
		};
	}
}
