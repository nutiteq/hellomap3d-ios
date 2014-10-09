#ifndef GLTEXTURE_H_
#define GLTEXTURE_H_

#include "nmlpackage/BaseTypes.h"

#include <cassert>
#include <list>
#include <map>
#include <memory>
#include <string>

namespace NMLPackage {

class Texture;
class Sampler;

class GLTexture {
public:
	GLTexture(std::shared_ptr<NMLPackage::Texture> texture);

	void create(const GLContextPtr& gl);
	void dispose(const GLContextPtr& gl);

	void bind(const GLContextPtr& gl);

	int getTextureSize() const;

	static void uncompressTexture(NMLPackage::Texture& texture);

private:
	static GLuint getSamplerWrapMode(int wrapMode);
	
	void updateSampler(const GLContextPtr& gl, bool hasSampler, NMLPackage::Sampler sampler, bool complete);
	void updateMipLevel(const GLContextPtr& gl, int level, const NMLPackage::Texture& texture);
	void updateMipMaps(const GLContextPtr& gl, const NMLPackage::Texture& texture);
	void uploadTexture(const GLContextPtr& gl);

	int _refCount;
	std::shared_ptr<NMLPackage::Texture> _texture;

	GLuint _glTextureId;
	std::weak_ptr<GLContext> _glContext;
	int _glSize;
};

typedef std::shared_ptr<GLTexture> GLTexturePtr;

}

#endif
