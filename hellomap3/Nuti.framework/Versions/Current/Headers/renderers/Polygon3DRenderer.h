#ifndef POLYGON3DRENDERER_H_
#define POLYGON3DRENDERER_H_

#include "utils/LRUTextureCache.h"

#include <deque>
#include <memory>
#include <mutex>

namespace Nuti {

class Options;
class Polygon3D;
class Polygon3DDrawData;
class Projection;
class Shader;
class ShaderManager;
class VectorElementClickInfo;
class ViewState;

class Polygon3DRenderer {
public:
	Polygon3DRenderer();
	virtual ~Polygon3DRenderer();
    
    void setOptions(const std::weak_ptr<Options>& options);

	void offsetLayerHorizontally(double offset);

	void onSurfaceCreated(ShaderManager& shaderManager);
	void onDrawFrame(float deltaSeconds, const ViewState& viewState);
	void onSurfaceDestroyed();

	void addElement(const std::shared_ptr<Polygon3D>& element);
	void refreshElements();
    void updateElement(const std::shared_ptr<Polygon3D>& element);
    void removeElement(const std::shared_ptr<Polygon3D>& element);
    
	void calculateRayIntersectedElements(const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir,
			const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;

private:
	static void BuildAndDrawBuffers(GLuint a_color,
                                    GLuint a_coord,
                                    GLuint a_normal,
                                    std::vector<unsigned char>& colorBuf,
                                    std::vector<float>& coordBuf,
                                    std::vector<float>& normalBuf,
                                    std::vector<const Polygon3DDrawData*>& drawDataBuffer,
                                    const ViewState& viewState);
    
    static std::shared_ptr<Bitmap> GetPolygon3DBitmap();
    
	static std::shared_ptr<Bitmap> _Polygon3DBitmap;
    
    void drawBatch(const ViewState& viewState);
    
    std::unique_ptr<Texture> _polygon3DTex;

	std::vector<std::shared_ptr<Polygon3D> > _elements;
	std::vector<std::shared_ptr<Polygon3D> > _tempElements;
    
    std::vector<const Polygon3DDrawData*> _drawDataBuffer;

    std::vector<unsigned char> _colorBuf;
	std::vector<float> _coordBuf;
    std::vector<float> _normalBuf;

	const Shader* _shader;
    GLuint _a_color;
	GLuint _a_coord;
    GLuint _a_normal;
	GLuint _a_texCoord;
    GLuint _u_ambientColor;
    GLuint _u_lightColor;
    GLuint _u_lightDir;
    GLuint _u_mvpMat;
    GLuint _u_tex;

    std::weak_ptr<Options> _options;
    
	mutable std::mutex _mutex;
};

}

#endif
