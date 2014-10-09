#pragma once

#include "Map.h"
#include "Logger.h"

#include <memory>
#include <string>

#include <pugixml.hpp>

namespace Nuti {
	namespace Mapnik {
		class MapParser {
		public:
			class SymbolizerFactory {
			public:
				virtual ~SymbolizerFactory() = default;

				virtual std::shared_ptr<Symbolizer> createSymbolizer(const pugi::xml_node& node, const std::shared_ptr<Map>& map) const = 0;
			};

			MapParser(const std::shared_ptr<SymbolizerFactory>& factory, const std::shared_ptr<Logger>& logger) : _symbolizerFactory(factory), _logger(logger) { }

			std::shared_ptr<Map> parseMap(const pugi::xml_document& doc);

		protected:
			const std::shared_ptr<SymbolizerFactory> _symbolizerFactory;
			const std::shared_ptr<Logger> _logger;
		};
	}
}
