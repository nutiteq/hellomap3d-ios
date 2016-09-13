/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_TILELAYER_H_
#define _NUTI_VT_TILELAYER_H_

#include "TileGeometry.h"
#include "TileLabel.h"

#include <memory>
#include <vector>
#include <numeric>

#include <boost/optional.hpp>

namespace Nuti { namespace VT {
	class TileLayer {
	public:
		explicit TileLayer(int layerIdx, float opacity, boost::optional<CompOp> compOp, std::vector<std::shared_ptr<TileGeometry>> geometries, std::vector<std::shared_ptr<TileLabel>> labels) : _layerIdx(layerIdx), _opacity(opacity), _compOp(std::move(compOp)), _geometries(std::move(geometries)), _labels(std::move(labels)) { }

		int getLayerIndex() const { return _layerIdx; }
		float getOpacity() const { return _opacity; }
		boost::optional<CompOp> getCompOp() const { return _compOp; }

		const std::vector<std::shared_ptr<TileGeometry>>& getGeometries() const { return _geometries; }
		const std::vector<std::shared_ptr<TileLabel>>& getLabels() const { return _labels; }

		std::size_t getResidentSize() const {
			return std::accumulate(_geometries.begin(), _geometries.end(), static_cast<std::size_t>(0), [](std::size_t size, const std::shared_ptr<TileGeometry>& geometry) { return size + geometry->getResidentSize(); }) + _labels.size() * sizeof(TileLabel);
		}

	private:
		const int _layerIdx;
		const float _opacity;
		const boost::optional<CompOp> _compOp;
		const std::vector<std::shared_ptr<TileGeometry>> _geometries;
		const std::vector<std::shared_ptr<TileLabel>> _labels;
	};
} }

#endif
