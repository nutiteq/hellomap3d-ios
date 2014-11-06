#pragma once

#include "TileGeometry.h"
#include "TileLabel.h"

#include <memory>
#include <vector>
#include <numeric>

namespace Nuti {
	namespace VT {
		class TileLayer {
		public:
			TileLayer(int layerIdx, float opacity, const std::vector<std::shared_ptr<TileGeometry>>& geometries, const std::vector<std::shared_ptr<TileLabel>>& labels) : _layerIdx(layerIdx), _opacity(opacity), _geometries(geometries), _labels(labels) { }

			int getLayerIndex() const { return _layerIdx; }
			float getOpacity() const { return _opacity; }

			const std::vector<std::shared_ptr<TileGeometry>>& getGeometries() const { return _geometries; }
			const std::vector<std::shared_ptr<TileLabel>>& getLabels() const { return _labels; }

			std::size_t getResidentSize() const {
				return std::accumulate(_geometries.begin(), _geometries.end(), 0, [](std::size_t size, const std::shared_ptr<TileGeometry>& geometry) { return size + geometry->getResidentSize(); }) + _labels.size() * sizeof(TileLabel);
			}

		private:
			const int _layerIdx;
			const float _opacity;
			const std::vector<std::shared_ptr<TileGeometry>> _geometries;
			const std::vector<std::shared_ptr<TileLabel>> _labels;
		};
	}
}
