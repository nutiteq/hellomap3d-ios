#pragma once

#include <string>

#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

namespace Nuti {
	namespace VT {
		class GLExtensions {
		public:
			GLExtensions();

			bool GL_OES_vertex_array_object_supported() const { return _GL_OES_vertex_array_object_supported; }
			void glBindVertexArrayOES(GLuint array);
			void glDeleteVertexArraysOES(GLsizei n, const GLuint* arrays);
			void glGenVertexArraysOES(GLsizei n, GLuint* arrays);
			GLboolean glIsVertexArrayOES(GLuint array);

			bool GL_EXT_texture_filter_anisotropic_supported() const { return _GL_EXT_texture_filter_anisotropic_supported; }

		private:
			bool _GL_OES_vertex_array_object_supported = false;
			bool _GL_EXT_texture_filter_anisotropic_supported = false;

#if !defined(__APPLE__) && defined(GL_OES_vertex_array_object)
			PFNGLBINDVERTEXARRAYOESPROC _glBindVertexArrayOES = nullptr;
			PFNGLDELETEVERTEXARRAYSOESPROC _glDeleteVertexArraysOES = nullptr;
			PFNGLGENVERTEXARRAYSOESPROC _glGenVertexArraysOES = nullptr;
			PFNGLISVERTEXARRAYOESPROC _glIsVertexArrayOES = nullptr;
#endif
		};
	}
}