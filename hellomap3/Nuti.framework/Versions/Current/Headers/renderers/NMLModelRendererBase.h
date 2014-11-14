#ifndef NMLMODELRENDERERBASE_H_
#define NMLMODELRENDERERBASE_H_

#include "drawdatas/nmlGL/BaseTypes.h"

#include <mutex>
#include <memory>

namespace Nuti {

class MapPos;
class MapVec;
class Shader;
class ShaderManager;
class VectorElementClickInfo;
class ViewState;

class NMLModelRendererBase {
public:
	virtual ~NMLModelRendererBase();

	virtual void offsetLayerHorizontally(double offset);

	virtual void onSurfaceCreated(ShaderManager& shaderManager);
	virtual bool onDrawFrame(float deltaSeconds, const ViewState& viewState);
	virtual void onSurfaceDestroyed();

protected:
	struct GLContext : nmlGL::GLContext {
		GLContext(const Shader &shader);
		virtual ~GLContext();

		const Shader& getShader();

		void setModelviewProjectionMatrix(const cglib::mat4x4<float>& mvpMatrix);
		virtual GLuint getUniformLocation(const char *name) const;
		virtual GLuint getAttribLocation(const char *name) const;
		virtual void setLocalModelviewMatrix(const float matrix[]);

	private:
		const Shader& _shader;
		cglib::mat4x4<float> _mvpMatrix;
	};

	NMLModelRendererBase();

	virtual bool drawModels(const ViewState& viewState) = 0;

	std::shared_ptr<GLContext> _glContext;
    
	mutable std::mutex _mutex;
};

}

#endif
