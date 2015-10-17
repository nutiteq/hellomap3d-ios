/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_TILE_H_
#define _NUTI_VT_TILE_H_

#include "TileId.h"
#include "TileLayer.h"

#include <memory>
#include <vector>
#include <numeric>

namespace Nuti { namespace VT {
	class Tile {
	public:
		Tile(const TileId& tileId, const std::vector<std::shared_ptr<TileLayer>>& layers) : _tileId(tileId), _layers(layers) { }

		const TileId& getTileId() const { return _tileId; }
		const std::vector<std::shared_ptr<TileLayer>>& getLayers() const { return _layers; }

		std::size_t getResidentSize() const {
			return sizeof(TileId) + std::accumulate(_layers.begin(), _layers.end(), static_cast<std::size_t>(0), [](std::size_t size, const std::shared_ptr<TileLayer>& layer) { return size + layer->getResidentSize(); });
		}

	private:
		const TileId _tileId;
		const std::vector<std::shared_ptr<TileLayer>> _layers;
	};
} }

#endif
