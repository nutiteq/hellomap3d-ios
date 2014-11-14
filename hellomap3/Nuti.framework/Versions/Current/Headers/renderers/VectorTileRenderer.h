#ifndef VECTORTILERENDERER_H_
#define VECTORTILERENDERER_H_

#include "graphics/Color.h"
#include "graphics/ViewState.h"
#include "vectortiles/VT/TileId.h"
#include "vectortiles/VT/Tile.h"
#include "vectortiles/VT/GLTileRendererBase.h"

#include <memory>
#include <mutex>
#include <map>

namespace Nuti {

class MapPos;
class Projection;
class Shader;
class ShaderManager;
class MapRenderer;
class ViewState;

class VectorTileRenderer : protected VT::GLTileRendererBase {
public:
	VectorTileRenderer(const std::weak_ptr<MapRenderer>& mapRenderer);
	virtual ~VectorTileRenderer();

	void offsetLayerHorizontally(double offset);

	void onSurfaceCreated(ShaderManager& shaderManager);
	bool onDrawFrame(float deltaSeconds, const ViewState& viewState);
	void onSurfaceDestroyed();

	void setBackgroundColor(const Color& color);
	void setBackgroundPattern(const std::shared_ptr<VT::BitmapPattern>& pattern);
	bool cullLabels(const ViewState& viewState);
	void refreshTiles(const std::map<VT::TileId, std::shared_ptr<VT::Tile> >& tiles);

protected:
	virtual void deleteBuffer(GLuint& buffer);
	virtual void deleteVertexArray(GLuint& vertexArray);
	virtual void deleteTexture(GLuint& texture);
	virtual GLuint createProgram(const std::string& name);
	virtual void deleteProgram(GLuint& program);
	virtual std::string readShader(const std::string& fileName) const;

private:
	std::weak_ptr<MapRenderer> _mapRenderer;
	std::map<std::string, Shader> _shaderMap;
	double _horizontalLayerOffset;
	bool _surfaceLost;

	mutable std::mutex _mutex;
};

}

#endif
