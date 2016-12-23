#pragma once

#include "Texture.h"

namespace bplr
{
	namespace graphics
	{
		void bindDefaultFramebuffer();
		void clearFramebuffer();

		class Framebuffer
		{
		public:
			Framebuffer(GLsizei width, GLsizei height, GLuint numColorBuffers);
			~Framebuffer();

			void bindForReading() const;
			void bindForWriting() const;
			void setReadBuffer(GLuint bufferIndex) const;
			void bindTexture(GLuint index, Shader* shader, std::string uniformName) const;

			void clear() const;

			void drawBuffers() const;

		private:
			GLsizei m_width, m_height;
			GLuint m_location;
			GLuint m_depthTexture;
			std::vector<Texture*> m_textures;
		};
	}
}
