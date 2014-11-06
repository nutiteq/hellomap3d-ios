#pragma once

#include "MapParser.h"

namespace Nuti {
	namespace MapnikVT {
		class TileSymbolizerFactory : public Mapnik::MapParser::SymbolizerFactory {
		public:
			TileSymbolizerFactory(const std::shared_ptr<Mapnik::Logger>& logger) : _logger(logger) { }

			virtual std::shared_ptr<Mapnik::Symbolizer> createSymbolizer(const pugi::xml_node& node, const std::shared_ptr<Mapnik::Map>& map) const override;

		protected:
			const std::shared_ptr<Mapnik::Logger> _logger;
		};
	}
}
