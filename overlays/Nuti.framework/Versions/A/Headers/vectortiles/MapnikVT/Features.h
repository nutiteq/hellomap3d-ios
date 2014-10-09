#pragma once

#include "Value.h"
#include "ExpressionContext.h"

#include <memory>
#include <list>
#include <vector>
#include <map>

#include <cglib/vec.h>

namespace Nuti {
	namespace MapnikVT {
		class Feature {
		public:
			using UserData = Mapnik::ExpressionContext::VariableMap;

			enum {
				POINT_GEOMETRY = Mapnik::POINT_GEOMETRY, LINE_GEOMETRY = Mapnik::LINE_GEOMETRY, POLYGON_GEOMETRY = Mapnik::POLYGON_GEOMETRY
			};

			virtual ~Feature() = default;

			long long getId() const { return _id; }
			
			const std::shared_ptr<UserData>& getUserData() const { return _userData; }
			
			virtual int getGeometryType() const = 0;

		protected:
			explicit Feature(long long id, const std::shared_ptr<UserData>& userData) : _id(id), _userData(userData) { }

			const long long _id;
			const std::shared_ptr<UserData> _userData;
		};

		class PointsFeature : public Feature {
		public:
			using Vertices = std::vector<cglib::vec2<float>>;

			PointsFeature(long long id, const std::shared_ptr<UserData>& userData, const std::shared_ptr<Vertices>& vertices) : Feature(id, userData), _vertices(vertices) { }

			virtual int getGeometryType() const override { return POINT_GEOMETRY; }

			const std::shared_ptr<Vertices>& getVertices() const { return _vertices; }

		private:
			const std::shared_ptr<Vertices> _vertices;
		};

		class LinesFeature : public Feature {
		public:
			using Vertices = std::vector<cglib::vec2<float>>;
			using VerticesList = std::list<Vertices>;

			LinesFeature(long long id, const std::shared_ptr<UserData>& userData, const std::shared_ptr<VerticesList>& verticesList) : Feature(id, userData), _verticesList(verticesList) { }

			virtual int getGeometryType() const override { return LINE_GEOMETRY; }

			const std::shared_ptr<VerticesList>& getVerticesList() const { return _verticesList; }

			std::vector<cglib::vec2<float>> getMidPoints() const {
				std::vector<cglib::vec2<float>> midPoints;
				for (const Vertices& vertices : *_verticesList) {
					if (vertices.empty()) {
						continue;
					}
					if (vertices.size() == 1) {
						midPoints.push_back(vertices.front());
						continue;
					}
					float pos = 0;
					for (std::size_t i = 1; i < vertices.size(); i++) {
						float len = cglib::length(vertices[i] - vertices[i - 1]);
						pos += len * 0.5f;
					}
					for (std::size_t i = 1; i < vertices.size(); i++) {
						float len = cglib::length(vertices[i] - vertices[i - 1]);
						if (pos <= len) {
							float t = pos / len;
							midPoints.push_back(vertices[i] * t + vertices[i - 1] * (1 - t));
							break;
						}
						pos -= len;
					}
				}
				return midPoints;
			}

		private:
			const std::shared_ptr<VerticesList> _verticesList;
		};

		class PolygonFeature : public Feature {
		public:
			using Vertices = std::vector<cglib::vec2<float>>;
			using VerticesList = std::list<Vertices>;

			PolygonFeature(long long id, const std::shared_ptr<UserData>& userData, const std::shared_ptr<VerticesList>& verticesList) : Feature(id, userData), _verticesList(verticesList) { }

			virtual int getGeometryType() const override { return POLYGON_GEOMETRY; }

			const std::shared_ptr<VerticesList>& getVerticesList() const { return _verticesList; }

			cglib::vec2<float> getCenterPoint() const {
				if (_verticesList->empty()) {
					return cglib::vec2<float>(0, 0);
				}
				const Vertices& vertices = _verticesList->front();
				cglib::vec2<float> center(0, 0);
				for (const cglib::vec2<float>& vertex : vertices) {
					center += vertex * (1.0f / vertices.size());
				}
				return center;
			}

		private:
			const std::shared_ptr<VerticesList> _verticesList;
		};
	}
}
