#pragma once

#include "Tile.h"

#include <vector>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <mutex>

#include "GLExtensions.h"

namespace Nuti {
	namespace VT {
		class GLTileRendererBase {
		public:
			GLTileRendererBase(std::mutex& mutex, const std::shared_ptr<GLExtensions>& glExtensions, float scale);
			virtual ~GLTileRendererBase() = default;

			void setViewState(const cglib::mat4x4<double>& projectionMatrix, const cglib::mat4x4<double>& cameraMatrix, float zoom, float aspectRatio);
			void setLightDir(const cglib::vec3<float>& lightDir);
			void setBackgroundColor(unsigned int backgroundColor);
			void setBackgroundPattern(const std::shared_ptr<BitmapPattern>& pattern);
			void setVisibleTiles(const std::map<TileId, std::shared_ptr<Tile>>& tiles);
			std::vector<std::shared_ptr<TileLabel>> getVisibleLabels() const;

			void initialize();
			void deinitialize();
			bool render(float dt);

		private:
			struct BlendNode {
				TileId tileId;
				std::shared_ptr<Tile> tile;
				float blend;
				std::vector<std::shared_ptr<BlendNode>> childNodes;

				BlendNode(const TileId& tileId, const std::shared_ptr<Tile>& tile, float blend) : tileId(tileId), tile(tile), blend(blend), childNodes() { }
			};

			struct RenderNode {
				TileId tileId;
				std::shared_ptr<TileLayer> layer;
				float blend;

				RenderNode(const TileId& tileId, const std::shared_ptr<TileLayer>& layer, float blend) : tileId(tileId), layer(layer), blend(blend) { }
			};

			struct CompiledBitmap {
				GLuint texture;

				CompiledBitmap() : texture(0) { }
			};

			struct CompiledGeometry {
				GLuint vertexGeometryVBO;
				GLuint indicesVBO;
				GLuint geometryVAO;

				CompiledGeometry() : vertexGeometryVBO(0), indicesVBO(0), geometryVAO(0) { }
			};

			static cglib::mat4x4<double> calculateLocalViewMatrix(const cglib::mat4x4<double>& cameraMatrix);

			cglib::mat3x3<double> calculateTileMatrix2d(const TileId& tileId) const;
			cglib::mat4x4<double> calculateTileMatrix(const TileId& tileId) const;
			cglib::bounding_box<double, 3> calculateTileBBox(const TileId& tileId) const;

			void updateBlendNode(const std::shared_ptr<BlendNode>& blendNode, float dBlend);
			void buildRenderNodes(const std::shared_ptr<BlendNode>& blendNode, float blend, std::multimap<int, RenderNode>& renderNodeMap);

			bool renderBlendNodes2D(const std::vector<std::shared_ptr<BlendNode>>& blendNodes);
			bool renderBlendNodes3D(const std::vector<std::shared_ptr<BlendNode>>& blendNodes);
			bool renderLabels(const std::vector<std::shared_ptr<TileLabel>>& labels, float dOpacity);

			void renderTileBackground(const TileId& tileId, float opacity);
			void renderTileGeometry(const TileId& tileId, const TileId& targetTileId, float blend, float opacity, const std::shared_ptr<TileGeometry>& geometry);
			void renderVertexDataList(const std::shared_ptr<const Bitmap>& bitmap, cglib::mat4x4<double>& mvMatrix, const VertexArray<cglib::vec3<float>>& vertices, const VertexArray<cglib::vec2<float>>& texCoords, const VertexArray<cglib::vec4<unsigned char>>& colors, const VertexArray<unsigned short>& indices);
			void checkGLError();

			virtual GLuint createBuffer();
			virtual void deleteBuffer(GLuint& buffer);
			virtual GLuint createVertexArray();
			virtual void deleteVertexArray(GLuint& vertexArray);
			virtual GLuint createTexture();
			virtual void deleteTexture(GLuint& texture);
			virtual GLuint createProgram(const std::string& programName);
			virtual void deleteProgram(GLuint& program);

			virtual std::string readShader(const std::string& fileName) const = 0;

			unsigned int _backgroundColor = 0;
			std::shared_ptr<BitmapPattern> _backgroundPattern;

			GLuint _lineShaderProgram = 0;
			GLuint _linePatternShaderProgram = 0;
			GLuint _polygonShaderProgram = 0;
			GLuint _polygonPatternShaderProgram = 0;
			GLuint _polygon3DShaderProgram = 0;
			GLuint _labelShaderProgram = 0;
			GLuint _backgroundShaderProgram = 0;
			GLuint _backgroundPatternShaderProgram = 0;

			GLuint _tileVerticesVBO = 0;

			GLuint _screenTexture = 0;

			cglib::vec3<float> _lightDir;
			cglib::mat4x4<double> _projectionMatrix;
			cglib::mat4x4<double> _cameraMatrix;
			cglib::frustum3<double> _frustum;
			cglib::mat4x4<double> _labelMatrix;
			TileLabel::ViewState _labelViewState;
			VertexArray<cglib::vec3<float>> _labelVertices;
			VertexArray<cglib::vec2<float>> _labelTexCoords;
			VertexArray<cglib::vec4<unsigned char>> _labelColors;
			VertexArray<unsigned short> _labelIndices;
			float _zoom = 0;
			float _halfResolution = 0;
			int _screenWidth = 0;
			int _screenHeight = 0;

			std::vector<std::shared_ptr<BlendNode>> _blendNodes;
			std::vector<std::shared_ptr<TileLabel>> _labels;
			std::unordered_map<long long, std::shared_ptr<TileLabel>> _labelMap;
			std::unordered_map<std::shared_ptr<const Bitmap>, CompiledBitmap> _compiledBitmapMap;
			std::unordered_map<std::shared_ptr<TileGeometry>, CompiledGeometry> _compiledGeometryMap;

			const float _scale;
			std::shared_ptr<GLExtensions> _glExtensions;
			std::mutex& _mutex;
		};
	}
}
