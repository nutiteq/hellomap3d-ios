#pragma once

#include "TileId.h"
#include "TileLayer.h"

#include <memory>
#include <vector>
#include <numeric>

namespace Nuti {
	namespace VT {
		class Tile {
		public:
			Tile(const TileId& tileId, const std::vector<std::shared_ptr<TileLayer>>& layers) : _tileId(tileId), _layers(layers) { }

			const TileId& getTileId() const { return _tileId; }
			const std::vector<std::shared_ptr<TileLayer>>& getLayers() const { return _layers; }

			std::size_t getResidentSize() const {
				return sizeof(TileId) + std::accumulate(_layers.begin(), _layers.end(), 0, [](std::size_t size, const std::shared_ptr<TileLayer>& layer) { return size + layer->getResidentSize(); });
			}

		private:
			const TileId _tileId;
			const std::vector<std::shared_ptr<TileLayer>> _layers;
		};
	}
}
