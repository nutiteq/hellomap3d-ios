/*
 * Copyright 2014 Nutiteq Llc. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://www.nutiteq.com/license/
 */

#ifndef _NUTI_MAPNIKVT_FEATURES_H_
#define _NUTI_MAPNIKVT_FEATURES_H_

#include "Value.h"
#include "ExpressionContext.h"

#include <memory>
#include <list>
#include <vector>
#include <map>

#include <cglib/vec.h>

namespace Nuti { namespace MapnikVT {
	class Feature {
	public:
		using UserData = Mapnik::ExpressionContext::VariableMap;
		using GeometryType = Mapnik::ExpressionContext::GeometryType;

		virtual ~Feature() = default;

		long long getId() const { return _id; }
			
		const std::shared_ptr<UserData>& getUserData() const { return _userData; }
			
		virtual GeometryType getGeometryType() const = 0;

	protected:
		explicit Feature(long long id, const std::shared_ptr<UserData>& userData) : _id(id), _userData(userData) { }

		const long long _id;
		const std::shared_ptr<UserData> _userData;
	};

	class PointsFeature : public Feature {
	public:
		using Vertices = std::vector<cglib::vec2<float>>;

		PointsFeature(long long id, const std::shared_ptr<UserData>& userData, const std::shared_ptr<Vertices>& vertices) : Feature(id, userData), _vertices(vertices) { }

		virtual GeometryType getGeometryType() const override { return GeometryType::POINT_GEOMETRY; }

		const std::shared_ptr<Vertices>& getVertices() const { return _vertices; }

	private:
		const std::shared_ptr<Vertices> _vertices;
	};

	class LinesFeature : public Feature {
	public:
		using Vertices = std::vector<cglib::vec2<float>>;
		using VerticesList = std::list<Vertices>;

		LinesFeature(long long id, const std::shared_ptr<UserData>& userData, const std::shared_ptr<VerticesList>& verticesList) : Feature(id, userData), _verticesList(verticesList) { }

		virtual GeometryType getGeometryType() const override { return GeometryType::LINE_GEOMETRY; }

		const std::shared_ptr<VerticesList>& getVerticesList() const { return _verticesList; }
		std::vector<cglib::vec2<float>> getMidPoints() const;

	private:
		const std::shared_ptr<VerticesList> _verticesList;
	};

	class PolygonFeature : public Feature {
	public:
		using Vertices = std::vector<cglib::vec2<float>>;
		using VerticesList = std::list<Vertices>;

		PolygonFeature(long long id, const std::shared_ptr<UserData>& userData, const std::shared_ptr<VerticesList>& verticesList) : Feature(id, userData), _verticesList(verticesList) { }

		virtual GeometryType getGeometryType() const override { return GeometryType::POLYGON_GEOMETRY; }

		const std::shared_ptr<VerticesList>& getVerticesList() const { return _verticesList; }
		cglib::vec2<float> getCenterPoint() const;

	private:
		const std::shared_ptr<VerticesList> _verticesList;
	};
} }

#endif
