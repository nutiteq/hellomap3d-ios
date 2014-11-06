#pragma once

#include "BitmapManager.h"
#include "FontManager.h"

#include <memory>

namespace Nuti {
	namespace MapnikVT {
		class TileSymbolizerContext {
		public:
			struct Settings {
				Settings(float geometryScale, float labelScale) : _geometryScale(geometryScale), _labelScale(labelScale) { }

				float getGeometryScale() const { return _geometryScale; }
				float getLabelScale() const { return _labelScale; }

			private:
				const float _geometryScale;
				const float _labelScale;
			};

			TileSymbolizerContext(const std::shared_ptr<VT::BitmapManager>& bitmapManager, const std::shared_ptr<VT::FontManager>& fontManager, const Settings& settings) : _bitmapManager(bitmapManager), _fontManager(fontManager), _settings(settings) { }

			std::shared_ptr<VT::BitmapManager> getBitmapManager() const { return _bitmapManager; }
			std::shared_ptr<VT::FontManager> getFontManager() const { return _fontManager; }
			const Settings& getSettings() const { return _settings; }

		private:
			const std::shared_ptr<VT::BitmapManager> _bitmapManager;
			const std::shared_ptr<VT::FontManager> _fontManager;
			const Settings _settings;
		};
	}
}
