#pragma once

#include "FreeImage.h"
#include <GL/glew.h>
#include "Shader.h"
#include <types.h>

namespace bplr
{
	namespace graphics
	{
		enum TextureType
		{
			DiffuseMap,
			SpecularMap,
		};

		static std::map<TextureType, std::string> typeNames = {
			{ DiffuseMap, "diffuseMap" },
			{ SpecularMap, "specularMap" },
		};

		class Texture
		{
		public:
			Texture(const char* filename, TextureType type = DiffuseMap, GLenum imageFormat = GL_BGRA, GLint internalFormat = GL_RGBA, GLint mipmapLevel = 0, GLint border = 0);
			~Texture();

			void bind(Shader *shader, const char *uniformName) const;

			TextureType getType() const;
			aiString getPath() const;

		private:
			TextureType m_type;
			aiString m_path;
			GLuint m_location;
		};
	}
}
