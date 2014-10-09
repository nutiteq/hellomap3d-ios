#ifndef WATERMARKRENDERER_H_
#define WATERMARKRENDERER_H_

#include "ui/BasemapView.h"
#include "utils/GLES2.h"
#include "utils/LicenseUtils.h"

#include <cglib/mat.h>
#include <memory>

namespace Nuti {

class Bitmap;
class Options;
class ShaderManager;
class Shader;
class Texture;
class ViewState;

class WatermarkRenderer {
public:
	WatermarkRenderer(const Options& options, WatermarkType::WatermarkType licenseType);
	virtual ~WatermarkRenderer();

	void onSurfaceCreated(ShaderManager& shaderManager);
    void onSurfaceChanged(int width, int height);
	void onDrawFrame(const ViewState& viewState);
	void onSurfaceDestroyed();

protected:
    static std::shared_ptr<Bitmap> GetEvaluationWatermarkBitmap();
	static std::shared_ptr<Bitmap> GetExpiredWatermarkBitmap();
    static std::shared_ptr<Bitmap> GetNutiteqWatermarkBitmap();
    
    static std::shared_ptr<Bitmap> _EvaluationWatermarkBitmap;
    static std::shared_ptr<Bitmap> _ExpiredWatermarkBitmap;
    static std::shared_ptr<Bitmap> _NutiteqWatermarkBitmap;
    
    const static int FIXED_WATERMARK_PADDING_X = 4;
    const static int FIXED_WATERMARK_PADDING_Y = 4;
    
    const static int WATERMARK_VERTEX_COUNT = 4;
    const static int WATERMARK_WIDTH_DP = 100;
    
    void drawWatermark(const ViewState& viewState);
    
    WatermarkType::WatermarkType _licenseType;
    
    float _randomAlignmentX;
    float _randomAlignmentY;

	std::shared_ptr<Bitmap> _watermarkBitmap;
	std::unique_ptr<Texture> _watermarkTex;
	float _watermarkCoords[WATERMARK_VERTEX_COUNT * 3];
    float _watermarkTexCoords[WATERMARK_VERTEX_COUNT * 2];
    
    cglib::mat4x4<float> _modelviewProjectionMat;
    
    bool _surfaceChanged;

	const Shader* _shader;
	GLuint _u_tex;
	GLuint _u_mvpMat;
	GLuint _a_coord;
	GLuint _a_texCoord;
	GLuint _a_color;

	const Options& _options;
};

}

#endif
