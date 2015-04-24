/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_TILEREADER_H_
#define _NUTI_MAPNIKVT_TILEREADER_H_

#include "TileSymbolizer.h"
#include "Expression.h"
#include "ExpressionContext.h"
#include "Rule.h"
#include "Filter.h"
#include "Map.h"
#include "Tile.h"
#include "FeaturesDecoder.h"

#include <memory>

#include <cglib/vec.h>
#include <cglib/mat.h>

namespace Nuti { namespace MapnikVT {
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
} }

#endif
