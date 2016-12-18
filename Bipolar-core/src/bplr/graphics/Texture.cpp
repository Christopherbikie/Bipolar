#include "Texture.h"
#include "FreeImage.h"
#include <ostream>
#include <iostream>

namespace bplr
{
	namespace graphics
	{
		Texture::Texture(std::string path)
			: m_path(path)
		{
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

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_location);
		}

		void Texture::bind(Shader *shader, const char *uniformName) const
		{
			GLuint location = glGetUniformLocation(shader->getLocation(), uniformName);
			glActiveTexture(GL_TEXTURE0 + location);
			glBindTexture(GL_TEXTURE_2D, m_location);
			glUniform1i(location, location);
		}

		GLubyte* Texture::loadToBitmap(std::string path)
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

			FIBITMAP* m_bitmap = FreeImage_Load(format, pathCStr);

			GLint bitsPerPixel = FreeImage_GetBPP(m_bitmap);
			FIBITMAP* m_bitmap32;
			if (bitsPerPixel == 32)
				m_bitmap32 = m_bitmap;
			else
				m_bitmap32 = FreeImage_ConvertTo32Bits(m_bitmap);

			m_width = FreeImage_GetWidth(m_bitmap32);
			m_height = FreeImage_GetHeight(m_bitmap32);

			return FreeImage_GetBits(m_bitmap32);
		}

		TextureData::TextureData(const char* filename)
		{
			FREE_IMAGE_FORMAT freeImageFormat = FIF_UNKNOWN;
			freeImageFormat = FreeImage_GetFileType(filename);
			if (freeImageFormat == FIF_UNKNOWN)
				freeImageFormat = FreeImage_GetFIFFromFilename(filename);
			if (freeImageFormat == FIF_UNKNOWN) {
				std::cout << "Failed to load image at " << filename << std::endl;
				return;
			}

			m_bitmap = 0;
			if (FreeImage_FIFSupportsReading(freeImageFormat))
				m_bitmap = FreeImage_Load(freeImageFormat, filename);
			if (!m_bitmap) {
				std::cout << "Failed to read image at " << filename << std::endl;
				return;
			}

			FreeImage_FlipVertical(m_bitmap);

			m_bits = FreeImage_GetBits(m_bitmap);
			m_width = FreeImage_GetWidth(m_bitmap);
			m_height = FreeImage_GetHeight(m_bitmap);
			if ((m_bits == 0) || (m_width == 0) || (m_height == 0)) {
				std::cout << "Failed to get image bits/height/width at " << filename << std::endl;
				return;
			}

			m_bitsPerPixel = FreeImage_GetBPP(m_bitmap);
			m_format = m_bitsPerPixel == 32 ? GL_BGRA : GL_BGR;
			m_internalFormat = m_bitsPerPixel == 32 ? GL_RGBA : GL_RGB;
		}

		TextureData::~TextureData()
		{
			FreeImage_Unload(m_bitmap);
		}

		BYTE* TextureData::getBits() const
		{
			return m_bits;
		}

		GLuint TextureData::getWidth() const
		{
			return m_width;
		}

		GLuint TextureData::getHeight() const
		{
			return m_height;
		}

		GLenum TextureData::getFormat() const
		{
			return m_format;
		}

		GLenum TextureData::getInternalFormat() const
		{
			return m_internalFormat;
		}

		GLint TextureData::getBitsPerPixel() const
		{
			return m_bitsPerPixel;
		}
	}
}
