#pragma once

#include "FreeImage.h"
#include <GL/glew.h>
#include "Shader.h"

namespace bplr
{
	namespace graphics
	{
		class Texture
		{
		public:
			Texture(const char* filename, GLenum imageFormat = GL_BGR, GLint internalFormat = GL_RGB, GLint mipmapLevel = 0, GLint border = 0);
			~Texture();

			void bind(Shader *shader, const char *uniformName) const;
		private:
			GLuint m_location;
		};
	}
}
