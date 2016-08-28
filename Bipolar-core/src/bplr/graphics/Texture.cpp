#include "Texture.h"
#include <FreeImage.h>
#include <iostream>
#include <types.h>

namespace bplr
{
	namespace graphics
	{
		Texture::Texture(const char* filename, TextureType type, GLint mipmapLevel, GLint border)
			: m_type(type), m_path(filename)
		{
			FREE_IMAGE_FORMAT freeImageFormat = FIF_UNKNOWN;
			freeImageFormat = FreeImage_GetFileType(filename);
			if (freeImageFormat == FIF_UNKNOWN)
				freeImageFormat = FreeImage_GetFIFFromFilename(filename);
			if (freeImageFormat == FIF_UNKNOWN) {
				std::cout << "Failed to load image at " << filename << std::endl;
				return;
			}

			FIBITMAP* bitmap = 0;
			if (FreeImage_FIFSupportsReading(freeImageFormat))
				bitmap = FreeImage_Load(freeImageFormat, filename);
			if (!bitmap) {
				std::cout << "Failed to read image at " << filename << std::endl;
				return;
			}

			BYTE* bits;
			unsigned int width, height;
			bits = FreeImage_GetBits(bitmap);
			width = FreeImage_GetWidth(bitmap);
			height = FreeImage_GetHeight(bitmap);
			if ((bits == 0) || (width == 0) || (height == 0)) {
				std::cout << "Failed to get image bits/height/width at " << filename << std::endl;
				return;
			}

			GLint bitsPerPixel = FreeImage_GetBPP(bitmap);
			GLuint imageFormat = bitsPerPixel == 32 ? GL_BGRA : GL_BGR;
			GLuint internalFormat = bitsPerPixel == 32 ? GL_RGBA : GL_RGB;

			glGenTextures(1, &m_location);
			glBindTexture(GL_TEXTURE_2D, m_location);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTexImage2D(GL_TEXTURE_2D, mipmapLevel, internalFormat, width, height, border, imageFormat, GL_UNSIGNED_BYTE, bits);
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

			FreeImage_Unload(bitmap);
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

		aiString Texture::getPath() const
		{
			return m_path;
		}
	}
}
