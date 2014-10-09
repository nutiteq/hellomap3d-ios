#ifndef GLMATERIAL_H_
#define GLMATERIAL_H_

#include "nmlpackage/BaseTypes.h"
#include "nmlpackage/GLTexture.h"

#include <cassert>
#include <list>
#include <map>
#include <string>

namespace NMLPackage {

class Material;
class ColorOrTexture;

class GLMaterial {
public:
	GLMaterial(const NMLPackage::Material& material, const std::map<std::string, GLTexturePtr>& textureMap);

	void replaceTexture(const std::string& textureId, const GLTexturePtr& glTexture);

	void bind(const GLContextPtr& gl);

	int getCulling() const;

private:

	struct ColorOrTexture {
		std::string textureId;
		GLTexturePtr texture;
		cglib::vec4<float> color;

		ColorOrTexture();
		ColorOrTexture(const NMLPackage::ColorOrTexture& colorOrTexture, const std::map<std::string, GLTexturePtr>& textureMap);
	};

	int _type;
	int _culling;
	bool _translucent;
	ColorOrTexture _diffuse;
	GLTexturePtr _nullTexture;
};

typedef std::shared_ptr<GLMaterial> GLMaterialPtr;

}

#endif
