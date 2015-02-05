/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_MAP_H_
#define _NUTI_MAPNIK_MAP_H_

#include "FontSet.h"
#include "Layer.h"
#include "Style.h"
#include "Parameter.h"
#include "NutiParameter.h"

#include <memory>
#include <string>
#include <vector>
#include <map>

#include <boost/lexical_cast.hpp>

namespace Nuti { namespace Mapnik {
	class Map {
	public:
		Map() = default;

		void setBackgroundColor(unsigned int backgroundColor) { _backgroundColor = backgroundColor; }
		unsigned int getBackgroundColor() const { return _backgroundColor; }

		void setBackgroundImage(const std::string& backgroundImage) { _backgroundImage = backgroundImage; }
		const std::string& getBackgroundImage() const { return _backgroundImage; }

		void setFontDirectory(const std::string& fontDirectory) { _fontDirectory = fontDirectory; }
		const std::string& getFontDirectory() const { return _fontDirectory; }

		void clearNutiParameters() {
			_nutiParameterMap.clear();
		}
		
		void addNutiParameter(const NutiParameter& param) {
			_nutiParameterMap.insert({ param.getName(), param });
		}
		
		const std::map<std::string, NutiParameter>& getNutiParameterMap() const {
			return _nutiParameterMap;
		}

		void clearParameters() {
			_parameterMap.clear();
		}

		void addParameter(const Parameter& param) {
			_parameterMap.insert({ param.getName(), param });
		}

		const std::map<std::string, Parameter>& getParameterMap() const { return _parameterMap; }

		void clearStyles() {
			_styles.clear();
			_styleMap.clear();
		}
			
		void addStyle(const std::shared_ptr<Style>& style) {
			_styles.push_back(style);
			_styleMap[style->getName()] = style;
		}
			
		const std::vector<std::shared_ptr<Style>>& getStyles() const { return _styles; }

		const std::shared_ptr<Style>& getStyle(const std::string& name) const {
			auto it = _styleMap.find(name);
			if (it == _styleMap.end()) {
				return _nullStyle;
			}
			return it->second;
		}

		void addFontSet(const std::shared_ptr<FontSet>& fontSet) {
			_fontSets.push_back(fontSet);
			_fontSetMap[fontSet->getName()] = fontSet;
		}
			
		const std::vector<std::shared_ptr<FontSet>>& getFontSets() const { return _fontSets; }

		const std::shared_ptr<FontSet>& getFontSet(const std::string& name) const {
			auto it = _fontSetMap.find(name);
			if (it == _fontSetMap.end()) {
				return _nullFontSet;
			}
			return it->second;
		}

		void clearFontSets() {
			_fontSets.clear();
			_fontSetMap.clear();
		}

		void clearLayers() {
			_layers.clear();
			_layerMap.clear();
		}

		void addLayer(const std::shared_ptr<Layer>& layer) {
			_layers.push_back(layer);
			_layerMap[layer->getName()] = layer;
		}

		const std::vector<std::shared_ptr<Layer>>& getLayers() const { return _layers; }

		const std::shared_ptr<Layer>& getLayer(const std::string& name) const {
			auto it = _layerMap.find(name);
			if (it == _layerMap.end()) {
				return _nullLayer;
			}
			return it->second;
		}

	private:
		unsigned int _backgroundColor = 0x00000000;
		std::string _backgroundImage;
		std::string _fontDirectory;
		std::map<std::string, NutiParameter> _nutiParameterMap;
		std::map<std::string, Parameter> _parameterMap;
		std::vector<std::shared_ptr<Style>> _styles;
		std::shared_ptr<Style> _nullStyle;
		std::map<std::string, std::shared_ptr<Style>> _styleMap;
		std::vector<std::shared_ptr<FontSet>> _fontSets;
		std::shared_ptr<FontSet> _nullFontSet;
		std::map<std::string, std::shared_ptr<FontSet>> _fontSetMap;
		std::vector<std::shared_ptr<Layer>> _layers;
		std::shared_ptr<Layer> _nullLayer;
		std::map<std::string, std::shared_ptr<Layer>> _layerMap;
	};
} }

#endif
