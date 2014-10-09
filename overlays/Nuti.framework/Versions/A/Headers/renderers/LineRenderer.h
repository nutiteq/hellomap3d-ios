#ifndef LINERENDERER_H_
#define LINERENDERER_H_

#include "utils/LRUTextureCache.h"

#include <deque>
#include <memory>
#include <mutex>
#include <vector>

namespace Nuti {

class Bitmap;
class Line;
class LineDrawData;
class Projection;
class Shader;
class ShaderManager;
class VectorElementClickInfo;
class ViewState;

class LineRenderer {
public:
    static void BuildAndDrawBuffers(GLuint a_color,
                                    GLuint a_coord,
                                    GLuint a_texCoord,
                                    std::vector<unsigned char>& colorBuf,
                                    std::vector<float>& coordBuf,
                                    std::vector<unsigned int>& indexBuf,
                                    std::vector<float>& texCoordBuf,
                                    std::vector<const LineDrawData*>& drawDataBuffer,
                                    LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache,
                                    const ViewState& viewState);
    
	LineRenderer();
	virtual ~LineRenderer();

	void offsetLayerHorizontally(double offset);

	void onSurfaceCreated(ShaderManager& shaderManager);
	void onDrawFrame(float deltaSeconds, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
	void onSurfaceDestroyed();

    void addElement(const std::shared_ptr<Line>& element);
	void refreshElements();
    void updateElement(const std::shared_ptr<Line>& element);
    void removeElement(const std::shared_ptr<Line>& element);

	void calculateRayIntersectedElements(const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir,
                                         const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;

private:
    void drawBatch(LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);

	std::vector<std::shared_ptr<Line> > _elements;
	std::vector<std::shared_ptr<Line> > _tempElements;
    
    std::vector<const LineDrawData*> _drawDataBuffer;

    std::vector<unsigned char> _colorBuf;
	std::vector<float> _coordBuf;
    std::vector<unsigned int> _indexBuf;
	std::vector<float> _texCoordBuf;

	const Shader* _shader;
    GLuint _a_color;
	GLuint _a_coord;
	GLuint _a_texCoord;
	GLuint _u_mvpMat;
    GLuint _u_tex;

	mutable std::mutex _mutex;
};

}

#endif
