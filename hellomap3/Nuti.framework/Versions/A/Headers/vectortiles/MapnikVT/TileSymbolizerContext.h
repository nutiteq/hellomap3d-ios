/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_TILESYMBOLIZERCONTEXT_H_
#define _NUTI_MAPNIKVT_TILESYMBOLIZERCONTEXT_H_

#include "BitmapManager.h"
#include "FontManager.h"
#include "StrokeSet.h"
#include "ExpressionContext.h"

#include <memory>

namespace Nuti { namespace MapnikVT {
	class TileSymbolizerContext {
	public:
		struct Settings {
			using NutiParameterValueMap = Mapnik::ExpressionContext::NutiParameterValueMap;

			Settings(float tileSize, const NutiParameterValueMap& nutiParameterValueMap);

			float getTileSize() const { return _tileSize; }
			float getGeometryScale() const { return _geometryScale; }
			float getFontScale() const { return _fontScale; }
			float getZoomLevelBias() const { return _zoomLevelBias; }

			const std::shared_ptr<NutiParameterValueMap>& getNutiParameterValueMap() const { return _nutiParameterValueMap; }

		private:
			float _tileSize;
			float _geometryScale;
			float _fontScale;
			float _zoomLevelBias;
			std::shared_ptr<NutiParameterValueMap> _nutiParameterValueMap;
		};

		TileSymbolizerContext(const std::shared_ptr<VT::BitmapManager>& bitmapManager, const std::shared_ptr<VT::FontManager>& fontManager, const std::shared_ptr<VT::StrokeSet>& strokeSet, const Settings& settings) : _bitmapManager(bitmapManager), _fontManager(fontManager), _strokeSet(strokeSet), _settings(settings) { }

		std::shared_ptr<VT::BitmapManager> getBitmapManager() const { return _bitmapManager; }
		std::shared_ptr<VT::FontManager> getFontManager() const { return _fontManager; }
		std::shared_ptr<VT::StrokeSet> getStrokeSet() const { return _strokeSet; }
		const Settings& getSettings() const { return _settings; }

	private:
		const std::shared_ptr<VT::BitmapManager> _bitmapManager;
		const std::shared_ptr<VT::FontManager> _fontManager;
		const std::shared_ptr<VT::StrokeSet> _strokeSet;
		const Settings _settings;
	};
} }

#endif
