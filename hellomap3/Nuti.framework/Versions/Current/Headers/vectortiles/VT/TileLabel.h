/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_VT_TILELABEL_H_
#define _NUTI_VT_TILELABEL_H_

#include "Bitmap.h"
#include "Font.h"
#include "VertexArray.h"
#include "TileLayerStyles.h"

#include <memory>
#include <array>
#include <list>
#include <vector>
#include <limits>

#include <boost/variant.hpp>
#include <boost/optional.hpp>

#include <cglib/vec.h>
#include <cglib/mat.h>
#include <cglib/bbox.h>
#include <cglib/frustum3.h>

namespace Nuti { namespace VT {
	class TileLabel {
	public:
		using Vertex = cglib::vec3<double>;
		using Vertices = std::vector<Vertex>;
		using VerticesList = std::list<Vertices>;

		struct ViewState {
			float scale;
			float aspect;
			std::array<cglib::vec3<float>, 3> orientation;
			cglib::vec3<double> origin;
			cglib::frustum3<double> frustum;

			ViewState(const cglib::mat4x4<double>& projectionMatrix, const cglib::mat4x4<double>& cameraMatrix, float zoom, float aspectRatio, float scaleFactor) {
				cglib::mat4x4<double> invCameraMatrix = cglib::inverse(cameraMatrix);
				scale = std::pow(2.0f, -zoom) * scaleFactor;
				aspect = aspectRatio;
				for (int i = 0; i < 3; i++) {
					orientation[i] = cglib::vec3<float>::convert(cglib::proj_o(cglib::col_vector(invCameraMatrix, i)));
				}
				origin = cglib::proj_p(cglib::col_vector(invCameraMatrix, 3));
				frustum = cglib::gl_projection_frustum(projectionMatrix * cameraMatrix);
			}
		};

		TileLabel(long long id, long long groupId, const std::shared_ptr<Font>& font, std::vector<Font::Glyph>&& glyphs, boost::variant<Vertex, VerticesList>&& position, LabelOrientation orientation, const boost::optional<cglib::mat3x3<float>>& transform, float scale, unsigned int color);

		long long getId() const { return _id; }
		long long getGroupId() const { return _groupId; }
		bool isValid() const { return (bool) _placement; }
		unsigned int getColor() const { return _color; }

		int getPriority() const { return _priority; }
		void setPriority(int priority) { _priority = priority; }

		float getMinimumGroupDistance() const { return _minimumGroupDistance; }
		void setMinimumGroupDistance(float distance) { _minimumGroupDistance = distance; }

		float getOpacity() const { return _opacity; }
		void setOpacity(float opacity) { _opacity = opacity; }

		bool isVisible() const { return _visible; }
		void setVisible(bool visible) { _visible = visible; }

		bool isActive() const { return _active; }
		void setActive(bool active) { _active = active; }

		bool isGeometryTransformed() const { return _geometryTransformed; }
		void applyGeometryTransform(const cglib::mat4x4<double>& transform);

		LabelOrientation getOrientation() const { return _orientation; }
		const std::shared_ptr<Font>& getFont() const { return _font; }
		const std::shared_ptr<Bitmap>& getBitmap() const { return _bitmap; }

		void copyPlacement(const std::shared_ptr<TileLabel>& label);
		bool updatePlacement(const ViewState& viewState);
		void updateFontBitmap();

		bool calculateCenter(cglib::vec3<double>& pos) const;
		bool calculateEnvelope(const ViewState& viewState, std::array<cglib::vec3<float>, 4>& envelope) const;
		bool calculateVertexData(const ViewState& viewState, VertexArray<cglib::vec3<float>>& vertices, VertexArray<cglib::vec2<float>>& texCoords, VertexArray<unsigned short>& indices) const;

	private:
		struct Placement {
			struct Edge {
				cglib::vec3<double> p0;
				cglib::vec3<double> p1;
				cglib::vec3<float> xAxis;
				float length;

				Edge(const cglib::vec3<double>& p0, const cglib::vec3<double>& p1) : p0(p0), p1(p1) {
					length = static_cast<float>(cglib::length(p1 - p0));
					xAxis = cglib::vec3<float>::convert(p1 - p0) * (1.0f / length);
				}
			};

			std::vector<Edge> edges;
			std::size_t index;
			cglib::vec3<double> pos;

			Placement(const std::vector<Edge>& edges, std::size_t index, const cglib::vec3<double>& pos) : edges(edges), index(index), pos(pos) { }
		};

		void setupCoordinateSystem(const ViewState& viewState, const std::shared_ptr<Placement>& placement, cglib::vec3<float>& origin, cglib::vec3<float>& xAxis, cglib::vec3<float>& yAxis) const;
		void buildPointVertexData(VertexArray<cglib::vec2<float>>& vertices, VertexArray<cglib::vec2<float>>& texCoords, VertexArray<unsigned short>& indices) const;
		bool buildLineVertexData(const std::shared_ptr<Placement>& placement, const ViewState& viewState, VertexArray<cglib::vec3<float>>& vertices, VertexArray<cglib::vec2<float>>& texCoords, VertexArray<unsigned short>& indices) const;
		
		std::shared_ptr<Placement> getPlacement(const ViewState& viewState) const;
		std::shared_ptr<Placement> findClippedPlacement(const ViewState& viewState, const Vertex& vertex) const;
		std::shared_ptr<Placement> findClippedPlacement(const ViewState& viewState, const VerticesList& vertices) const;

		const float MIN_DOT = 0.866f; // minimum dot product between consecutive segments, to avoid very distorted placement. 0.886 is approx cos(30deg)
		const int EXTRA_PIXELS = 30; // number of extra pixels of space required around text
		const cglib::vec3<float> NORMAL = cglib::vec3<float>(0, 0, 1);

		const long long _id;
		const long long _groupId;
		std::shared_ptr<Font> _font;
		std::shared_ptr<Bitmap> _bitmap;
		std::vector<Font::Glyph> _glyphs;
		LabelOrientation _orientation;
		boost::variant<Vertex, VerticesList> _position;
		cglib::bounding_box<float, 2> _bbox;
		boost::optional<cglib::mat3x3<float>> _transform;
		float _scale;
		unsigned int _color;

		int _priority = 0;
		float _minimumGroupDistance = std::numeric_limits<float>::infinity();
		float _opacity = 0.0f;
		bool _visible = false;
		bool _active = false;
		bool _geometryTransformed = false;

		std::shared_ptr<Placement> _placement;
		std::shared_ptr<Placement> _flippedPlacement;

		mutable VertexArray<cglib::vec2<float>> _cachedVertices;
		mutable VertexArray<cglib::vec2<float>> _cachedTexCoords;
		mutable VertexArray<unsigned short> _cachedIndices;
	};
} }

#endif
