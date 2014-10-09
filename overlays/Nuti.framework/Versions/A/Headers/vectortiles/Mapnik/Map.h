#pragma once

#include "FontSet.h"
#include "Layer.h"
#include "Style.h"

#include <memory>
#include <string>
#include <vector>
#include <map>

#include <boost/lexical_cast.hpp>

namespace Nuti {
	namespace Mapnik {
		class Map {
		public:
			Map() = default;

			void setBackgroundColor(unsigned int backgroundColor) { _backgroundColor = backgroundColor; }
			unsigned int getBackgroundColor() const { return _backgroundColor; }

			void setBackgroundImage(const std::string& backgroundImage) { _backgroundImage = backgroundImage; }
			const std::string& getBackgroundImage() const { return _backgroundImage; }

			void setFontDirectory(const std::string& fontDirectory) { _fontDirectory = fontDirectory; }
			const std::string& getFontDirectory() const { return _fontDirectory; }

			const std::map<std::string, std::string>& getParameterMap() const { return _parameterMap; }

			template <typename T>
			T getParameter(const std::string& name, const T& defaultValue) const {
				auto it = _parameterMap.find(name);
				if (it == _parameterMap.end()) {
					return defaultValue;
				}
				return boost::lexical_cast<T>(it->second);
			}

			void clearParameters() {
				_parameterMap.clear();
			}

			void setParameter(const std::string& name, const std::string& value) {
				_parameterMap[name] = value;
			}

			const std::vector<std::shared_ptr<Style>>& getStyles() const { return _styles; }

			const std::shared_ptr<Style>& getStyle(const std::string& name) const {
				auto it = _styleMap.find(name);
				if (it == _styleMap.end()) {
					return _nullStyle;
				}
				return it->second;
			}

			void clearStyles() {
				_styles.clear();
				_styleMap.clear();
			}
			
			void addStyle(const std::shared_ptr<Style>& style) {
				_styles.push_back(style);
				_styleMap[style->getName()] = style;
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
			
			void addFontSet(const std::shared_ptr<FontSet>& fontSet) {
				_fontSets.push_back(fontSet);
				_fontSetMap[fontSet->getName()] = fontSet;
			}
			
			const std::vector<std::shared_ptr<Layer>>& getLayers() const { return _layers; }

			const std::shared_ptr<Layer>& getLayer(const std::string& name) const {
				auto it = _layerMap.find(name);
				if (it == _layerMap.end()) {
					return _nullLayer;
				}
				return it->second;
			}

			void clearLayers() {
				_layers.clear();
				_layerMap.clear();
			}
			
			void addLayer(const std::shared_ptr<Layer>& layer) {
				_layers.push_back(layer);
				_layerMap[layer->getName()] = layer;
			}
			
		private:
			unsigned int _backgroundColor = 0x00000000;
			std::string _backgroundImage;
			std::string _fontDirectory;
			std::map<std::string, std::string> _parameterMap;
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
	}
}
