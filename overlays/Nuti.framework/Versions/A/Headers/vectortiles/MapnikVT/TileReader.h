#pragma once

#include "TileSymbolizer.h"
#include "Expression.h"
#include "ConstExpression.h"
#include "ExpressionContext.h"
#include "Rule.h"
#include "Filter.h"
#include "Map.h"
#include "Tile.h"
#include "FeaturesDecoder.h"

#include <memory>

#include <cglib/vec.h>
#include <cglib/mat.h>

namespace Nuti {
	namespace MapnikVT {
		class TileReader {
		public:
			TileReader(const std::shared_ptr<Mapnik::Map>& map, const TileSymbolizerContext& symbolizerContext);
			virtual ~TileReader() = default;

			std::shared_ptr<VT::Tile> readTile(const VT::TileId& tileId, const FeaturesDecoder& featuresDecoder) const;

		private:
			void processStyle(const std::shared_ptr<Mapnik::Style>& mapnikStyle, Mapnik::ExpressionContext& exprContext, const std::shared_ptr<FeaturesDecoder::Features>& features, VT::TileLayerBuilder& layerBuilder) const;

			const std::shared_ptr<Mapnik::Map> _map;
			const TileSymbolizerContext& _symbolizerContext;
			const std::shared_ptr<Mapnik::Filter> _trueFilter;
		};
	}
}
