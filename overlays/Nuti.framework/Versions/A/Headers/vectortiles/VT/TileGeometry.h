#pragma once

#include "Bitmap.h"
#include "VertexArray.h"

#include <memory>
#include <vector>

namespace Nuti {
	namespace VT {
		class TileGeometry {
		public:
			enum class Type {
				NONE, LINE, POLYGON, POLYGON3D
			};

			struct StyleParameters {
				std::vector<unsigned int> colorTable;
				std::vector<float> lineWidthTable;
				std::shared_ptr<const BitmapPattern> pattern;

				StyleParameters() : colorTable(), lineWidthTable(), pattern() { }
			};

			struct GeometryLayoutParameters {
				int vertexSize;
				int vertexOffset;
				int attribsOffset;
				int texCoordOffset;
				int binormalOffset;
				int heightOffset;
				float vertexScale;
				float texCoordScale;
				float binormalScale;

				GeometryLayoutParameters() : vertexSize(0), vertexOffset(-1), attribsOffset(-1), texCoordOffset(-1), binormalOffset(-1), heightOffset(-1), vertexScale(0), texCoordScale(0), binormalScale(0) { }
			};

			TileGeometry(Type type, const StyleParameters& styleParameters, const GeometryLayoutParameters& geometryLayoutParameters, unsigned int indicesCount, VertexArray<unsigned char>&& vertexGeometry, VertexArray<unsigned short>&& indices) : _type(type), _styleParameters(styleParameters), _geometryLayoutParameters(geometryLayoutParameters), _indicesCount(indicesCount), _vertexGeometry(std::move(vertexGeometry)), _indices(std::move(indices)) { }

			Type getType() const { return _type; }
			const StyleParameters& getStyleParameters() const { return _styleParameters; }
			const GeometryLayoutParameters& getGeometryLayoutParameters() const { return _geometryLayoutParameters; }
			unsigned int getIndicesCount() const { return _indicesCount; }

			const VertexArray<unsigned char>& getVertexGeometry() const { return _vertexGeometry; }
			const VertexArray<unsigned short>& getIndices() const { return _indices; }

			void releaseVertexArrays() {
				_vertexGeometry.clear();
				_indices.clear();
			}

			std::size_t getResidentSize() const {
				return _vertexGeometry.size() * sizeof(unsigned char) + _indices.size() * sizeof(unsigned short);
			}

		private:
			Type _type;
			StyleParameters _styleParameters;
			GeometryLayoutParameters _geometryLayoutParameters;
			unsigned int _indicesCount;

			VertexArray<unsigned char> _vertexGeometry;
			VertexArray<unsigned short> _indices;
		};
	}
}
