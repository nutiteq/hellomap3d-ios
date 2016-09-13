/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_SYMBOLIZERCONTEXT_H_
#define _NUTI_MAPNIKVT_SYMBOLIZERCONTEXT_H_

#include "ExpressionContext.h"
#include "VT/BitmapManager.h"
#include "VT/FontManager.h"
#include "VT/StrokeMap.h"
#include "VT/GlyphMap.h"

#include <memory>

namespace Nuti { namespace MapnikVT {
	class SymbolizerContext {
	public:
		struct Settings {
            explicit Settings(float tileSize, std::map<std::string, Value> nutiParameterValueMap);

			float getTileSize() const { return _tileSize; }
			float getGeometryScale() const { return _geometryScale; }
			float getFontScale() const { return _fontScale; }
			float getZoomLevelBias() const { return _zoomLevelBias; }

			const std::map<std::string, Value>& getNutiParameterValueMap() const { return _nutiParameterValueMap; }

		private:
			float _tileSize;
			float _geometryScale;
			float _fontScale;
			float _zoomLevelBias;
			std::map<std::string, Value> _nutiParameterValueMap;
		};

        explicit SymbolizerContext(std::shared_ptr<VT::BitmapManager> bitmapManager, std::shared_ptr<VT::FontManager> fontManager, std::shared_ptr<VT::StrokeMap> strokeMap, std::shared_ptr<VT::GlyphMap> glyphMap, const Settings& settings) : _bitmapManager(std::move(bitmapManager)), _fontManager(std::move(fontManager)), _strokeMap(std::move(strokeMap)), _glyphMap(std::move(glyphMap)), _settings(settings) { }

		std::shared_ptr<VT::BitmapManager> getBitmapManager() const { return _bitmapManager; }
		std::shared_ptr<VT::FontManager> getFontManager() const { return _fontManager; }
		std::shared_ptr<VT::StrokeMap> getStrokeMap() const { return _strokeMap; }
        std::shared_ptr<VT::GlyphMap> getGlyphMap() const { return _glyphMap; }
        const Settings& getSettings() const { return _settings; }

	private:
		const std::shared_ptr<VT::BitmapManager> _bitmapManager;
		const std::shared_ptr<VT::FontManager> _fontManager;
		const std::shared_ptr<VT::StrokeMap> _strokeMap;
        const std::shared_ptr<VT::GlyphMap> _glyphMap;
		const Settings _settings;
	};
} }

#endif
