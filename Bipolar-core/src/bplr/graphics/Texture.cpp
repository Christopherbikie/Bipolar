#include "Texture.h"
#include "FreeImage.h"
#include <ostream>
#include <iostream>
#include "TextureStore.h"

namespace bplr
{
	namespace graphics
	{
		Texture::Texture(std::string path)
			: m_path(path)
		{
//			Texture* previousTexture = TextureStore::get(m_path);
//			if (previousTexture != nullptr)
//			{
//				m_location = previousTexture->getLocation();
//				m_width = previousTexture->getWidth();
//				m_height = previousTexture->getHeight();
//				return;
//			}
//			TextureStore::add(this);

			GLubyte* textureData = loadToBitmap(m_path);

			glGenTextures(1, &m_location);
			glBindTexture(GL_TEXTURE_2D, m_location);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glGenerateMipmap(GL_TEXTURE_2D);

			GLuint bitsPerPixel = FreeImage_GetBPP(m_bitmap);
			FreeImage_Unload(m_bitmap32);
			if (bitsPerPixel != 32)
				FreeImage_Unload(m_bitmap);
		}

		Texture::Texture(std::string path, GLenum cubemapFace)
			: m_path(path)
		{
			if (cubemapFace < GL_TEXTURE_CUBE_MAP_POSITIVE_X || cubemapFace > GL_TEXTURE_CUBE_MAP_NEGATIVE_Z)
			{
				std::cout << "Invalid cubemap face " << m_path << std::endl;
				return;
			}

			GLubyte* textureData = loadToBitmap(m_path, true);

			glTexImage2D(cubemapFace, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData);
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_location);
		}

		GLuint Texture::getLocation() const
		{
			return m_location;
		}


		std::string Texture::getPath() const
		{
			return m_path;
		}

		GLuint Texture::getWidth() const
		{
			return m_width;
		}

		GLuint Texture::getHeight() const
		{
			return m_height;
		}

		void Texture::bind(Shader *shader, const char *uniformName) const
		{
			GLuint location = glGetUniformLocation(shader->getLocation(), uniformName);
			glActiveTexture(GL_TEXTURE0 + location);
			glBindTexture(GL_TEXTURE_2D, m_location);
			glUniform1i(location, location);
		}

		GLubyte* Texture::loadToBitmap(std::string path, bool flip)
		{
			const char* pathCStr = path.c_str();

			FREE_IMAGE_FORMAT format = FIF_UNKNOWN;
			format = FreeImage_GetFileType(pathCStr);
			if (format == FIF_UNKNOWN)
				format = FreeImage_GetFIFFromFilename(pathCStr);
			if (format == FIF_UNKNOWN) {
				std::cout << "Failed to load image at " << pathCStr << std::endl;
				return nullptr;
			}
			if (!FreeImage_FIFSupportsReading(format))
			{
				std::cout << "Detected image format cannot be read! " << pathCStr << std::endl;
				return nullptr;
			}

			m_bitmap = FreeImage_Load(format, pathCStr);
			if (flip)
				FreeImage_FlipVertical(m_bitmap);

			GLint bitsPerPixel = FreeImage_GetBPP(m_bitmap);
			if (bitsPerPixel == 32)
				m_bitmap32 = m_bitmap;
			else
				m_bitmap32 = FreeImage_ConvertTo32Bits(m_bitmap);

			m_width = FreeImage_GetWidth(m_bitmap32);
			m_height = FreeImage_GetHeight(m_bitmap32);

			return FreeImage_GetBits(m_bitmap32);
		}
	}
}
