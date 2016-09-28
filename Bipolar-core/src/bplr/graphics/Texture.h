#pragma once

#include <GL/glew.h>
#include "Shader.h"
#include <FreeImage.h>

namespace bplr
{
	namespace graphics
	{
		enum TextureType
		{
			AlbedoMap,
			GlossMap,
			NormalMap,
			SpecularMap,
		};

		static std::map<TextureType, std::string> typeNames = {
			{ AlbedoMap, "albedo" },
			{ GlossMap, "gloss" },
			{ NormalMap, "normal" },
			{ SpecularMap, "specular" },
		};

		class Texture
		{
		public:
			Texture(const char* filename, TextureType type = AlbedoMap, GLint mipmapLevel = 0, GLint border = 0);
			~Texture();

			void bind(Shader *shader, const char *uniformName) const;

			TextureType getType() const;

		private:
			TextureType m_type;
			GLuint m_location;
		};

		class TextureData
		{
		public:
			TextureData(const char* filename);
			~TextureData();

			BYTE* getBits() const;
			GLuint getWidth() const;
			GLuint getHeight() const;
			GLenum getFormat() const;
			GLenum getInternalFormat() const;
			GLint getBitsPerPixel() const;
		
		private:
			BYTE* m_bits;
			GLuint m_width;
			GLuint m_height;
			GLenum m_format;
			GLenum m_internalFormat;
			GLint m_bitsPerPixel;

			FIBITMAP* m_bitmap;
		};
	}
}
