/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_TILELAYERBUILDER_H_
#define _NUTI_VT_TILELAYERBUILDER_H_

#include "TileGeometry.h"
#include "TileLabel.h"
#include "TileLayer.h"
#include "TileLayerStyles.h"
#include "PoolAllocator.h"
#include "VertexArray.h"

#include <memory>
#include <vector>
#include <list>

#include <boost/variant.hpp>

#include <cglib/vec.h>
#include <cglib/mat.h>
#include <cglib/bbox.h>

namespace Nuti { namespace VT {
	class TileLayerBuilder {
	public:
		using Vertex = cglib::vec2<float>;
		using Vertices = std::vector<Vertex>;
		using VerticesList = std::list<Vertices>;

		explicit TileLayerBuilder(float tileSize);

		void addLines(const VerticesList& verticesList, const LineStyle& style);
		void addPolygon(const VerticesList& verticesList, const PolygonStyle& style);
		void addPolygon3D(const VerticesList& verticesList, float height, const Polygon3DStyle& style);
		void addBitmapLabel(long long id, long long groupId, const Vertex& position, float minimumGroupDistance, const BitmapLabelStyle& style);
		void addTextLabel(long long id, long long groupId, const std::string& text, const boost::variant<Vertex, VerticesList>& position, float minimumGroupDistance, const TextLabelStyle& style);

		std::shared_ptr<TileLayer> build(int layerIdx, float opacity);

	private:
		struct StyleBuilderParameters : TileGeometry::StyleParameters {
			TileGeometry::Type type;
			std::array<StrokeSet::StrokeId, MAX_PARAMETERS> lineStrokeIds;
			std::shared_ptr<StrokeSet> strokeSet;

			StyleBuilderParameters() : StyleParameters(), type(TileGeometry::Type::NONE), lineStrokeIds(), strokeSet() { }
		};

		void appendGeometry();
		void appendGeometry(float verticesScale, float binormalsScale, float texCoordsScale, const VertexArray<cglib::vec2<float>>& vertices, const VertexArray<cglib::vec2<float>>& texCoords, const VertexArray<cglib::vec2<float>>& binormals, const VertexArray<float>& heights, const VertexArray<cglib::vec4<char>>& attribs, const VertexArray<unsigned int>& indices, std::size_t offset, std::size_t count);
		float calculateScale(VertexArray<cglib::vec2<float>>& values) const;

		bool tesselatePolygon(const VerticesList& verticesList, char styleIndex, const PolygonStyle& style);
		bool tesselatePolygon3D(const VerticesList& verticesList, float height, char styleIndex, const Polygon3DStyle& style);
		bool tesselateLine(const Vertices& points, char styleIndex, const StrokeSet::Stroke& stroke, const LineStyle& style);
		bool tesselateLineEndPoint(const Vertex& p0, float u0, float v0, float v1, int i0, const cglib::vec2<float>& tangent, const cglib::vec2<float>& binormal, char styleIndex, const LineStyle& style);

		const std::size_t RESERVED_VERTICES = 4096;
		const float MIN_MITER_DOT = -0.8f;

		float _tileSize;
		StyleBuilderParameters _styleParameters;

		VertexArray<cglib::vec2<float>> _vertices;
		VertexArray<cglib::vec2<float>> _texCoords;
		VertexArray<cglib::vec2<float>> _binormals;
		VertexArray<float> _heights;
		VertexArray<cglib::vec4<char>> _attribs;
		VertexArray<unsigned int> _indices;

		std::vector<std::shared_ptr<TileGeometry>> _geometryList;
		std::vector<std::shared_ptr<TileLabel>> _labelList;

		std::shared_ptr<PoolAllocator> _tessPoolAllocator;
	};
} }

#endif
