#ifndef BILLBOARDRENDERER_H_
#define BILLBOARDRENDERER_H_

#include "renderers/components/BillboardSorter.h"
#include "utils/LRUTextureCache.h"

#include <deque>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace Nuti {

class Billboard;
class BillboardDrawData;
class Bitmap;
class Projection;
class Shader;
class ShaderManager;
class VectorElementClickInfo;
class ViewState;

class BillboardRenderer {
public:
    static void CalculateBillboardCoords(const BillboardDrawData& drawData, const ViewState& viewState,
                                         std::vector<float>& coordBuf, int drawDataIndex);
    
	BillboardRenderer();
	virtual ~BillboardRenderer();

	virtual void offsetLayerHorizontally(double offset);

	void onSurfaceCreated(ShaderManager& shaderManager);
	void onDrawFrame(float deltaSeconds, BillboardSorter& billboardSorter, LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);
	void onDrawFrameSorted(float deltaSeconds,
                           const std::vector<std::shared_ptr<Billboard> >& billboardsBuffer,
                           LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache,
			const ViewState& viewState);
	void onSurfaceDestroyed();

    void addElement(const std::shared_ptr<Billboard>& element);
	void refreshElements();
    void updateElement(const std::shared_ptr<Billboard>& element);
    void removeElement(const std::shared_ptr<Billboard>& element);

	virtual void calculateRayIntersectedElements(const std::vector<std::shared_ptr<Billboard> >& billboardsBuffer,
                                                 const Projection& projection, const MapPos& rayOrig, const MapVec& rayDir,
                                                 const ViewState& viewState, std::vector<VectorElementClickInfo>& results) const;

private:
    static void BuildAndDrawBuffers(GLuint a_color,
                                    GLuint a_coord,
                                    GLuint a_texCoord,
                                    std::vector<unsigned char>& colorBuf,
                                    std::vector<float>& coordBuf,
                                    std::vector<unsigned int>& indexBuf,
                                    std::vector<float>& texCoordBuf,
                                    std::vector<const BillboardDrawData*>& drawDataBuffer,
                                    const MapBounds& texCoordBounds,
                                    LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache,
                                    const ViewState& viewState);
    
    bool calculateBaseBillboardDrawData(const std::shared_ptr<BillboardDrawData>& drawData, const ViewState& viewState);
    
    void drawBatch(LRUTextureCache<std::shared_ptr<Bitmap> >& styleCache, const ViewState& viewState);

	std::vector<std::shared_ptr<Billboard> > _elements;
	std::vector<std::shared_ptr<Billboard> > _tempElements;
    
    std::vector<const BillboardDrawData*> _drawDataBuffer;
    
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

	mutable std::recursive_mutex _mutex;
};

}

#endif
