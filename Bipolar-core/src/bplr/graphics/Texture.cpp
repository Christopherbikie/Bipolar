#include "Texture.h"
#include <FreeImage.h>
#include <iostream>

namespace bplr
{
	namespace graphics
	{
		Texture::Texture(TextureType type)
			: m_type(type)
		{
			unsigned char* data;

			// Allocate the needed space.
			int width = 128;
			int height = 128;

			data = new unsigned char[width * height * 4];

			for (int i = 0; i < (int)(width * height * 4); i++)
				data[i] = 0;

			// Generate white OpenGL texture.
			glGenTextures(1, &m_location);
			glBindTexture(GL_TEXTURE_2D, m_location);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}

		Texture::Texture(const char* filename, TextureType type, GLint mipmapLevel, GLint border)
			: m_type(type)
		{
			TextureData data = TextureData(filename);

			glGenTextures(1, &m_location);
			glBindTexture(GL_TEXTURE_2D, m_location);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, mipmapLevel, data.getInternalFormat(), data.getWidth(), data.getHeight(), border, data.getFormat(), GL_UNSIGNED_BYTE, data.getBits());
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			// Print pixel values (slow on big images)
//			for (int y = 0; y < height; ++y)
//			{
//				BYTE *pixel = (BYTE*)bits;
//				for (int x = 0; x < width; ++x)
//				{
//					std::cout << +pixel[FI_RGBA_RED] << " " << +pixel[FI_RGBA_GREEN] << " " << +pixel[FI_RGBA_BLUE] << std::endl;
//					pixel += 3;
//				}
//				bits += pitch;
//			}

			// Print bits per pixel
//			std::cout << bitsPerPixel << std::endl;
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

		TextureType Texture::getType() const
		{
			return m_type;
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
