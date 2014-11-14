/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIK_MAPPARSER_H_
#define _NUTI_MAPNIK_MAPPARSER_H_

#include "Map.h"
#include "Logger.h"

#include <memory>
#include <string>

#include <pugixml.hpp>

namespace Nuti { namespace Mapnik {
	class MapParser {
	public:
		class SymbolizerFactory {
		public:
			virtual ~SymbolizerFactory() = default;

			virtual std::shared_ptr<Symbolizer> createSymbolizer(const pugi::xml_node& node, const std::shared_ptr<Map>& map) const = 0;
		};

		MapParser(const std::shared_ptr<SymbolizerFactory>& factory, const std::shared_ptr<Logger>& logger) : _symbolizerFactory(factory), _logger(logger) { }

		std::shared_ptr<Map> parseMap(const pugi::xml_document& doc) const;

	protected:
		Value parseValue(const std::string& type, const std::string& value) const;

		const std::shared_ptr<SymbolizerFactory> _symbolizerFactory;
		const std::shared_ptr<Logger> _logger;
	};
} }

#endif
