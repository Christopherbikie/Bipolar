#include "GBuffer.h"
#include <iostream>
#include "FrameBuffer.h"

namespace bplr
{
	namespace graphics
	{
		GBuffer::GBuffer()
			: m_location(0), m_depthTexture(0)
		{
		}

		GBuffer::~GBuffer()
		{
			glDeleteFramebuffers(1, &m_location);
			glDeleteTextures(GBUFFER_NUM_TEXURES, m_textures);
			glDeleteTextures(1, &m_depthTexture);
		}

		void GBuffer::init(GLuint width, GLuint height)
		{
			glGenFramebuffers(1, &m_location);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_location);

			glGenTextures(GBUFFER_NUM_TEXURES, m_textures);
			glGenTextures(1, &m_depthTexture);

			for (GLuint i = 0; i < GBUFFER_NUM_TEXURES; ++i)
			{
				glBindTexture(GL_TEXTURE_2D, m_textures[i]);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
			}

			glBindTexture(GL_TEXTURE_2D, m_depthTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

			GLenum drawBuffers[GBUFFER_NUM_TEXURES];
			for (int i = 0; i < GBUFFER_NUM_TEXURES; ++i)
				drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
			glDrawBuffers(GBUFFER_NUM_TEXURES, drawBuffers);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "Failed to complete framebuffer! GLenum " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;

			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		}

		void GBuffer::bindForReading() const
		{
			glBindFramebuffer(GL_READ_FRAMEBUFFER, m_location);
		}

		void GBuffer::bindForWriting() const
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_location);
		}

		void GBuffer::setReadBuffer(GBufferTextureType buffer) const
		{
			glReadBuffer(GL_COLOR_ATTACHMENT0 + buffer);
		}

		void GBuffer::clear() const
		{
			clearFramebuffer();
		}

		void GBuffer::drawBuffers(GLsizei width, GLsizei height) const
		{
			GLsizei halfWidth = (GLsizei)(width / 2.0f);
			GLsizei halfHeight = (GLsizei)(height / 2.0f);

			setReadBuffer(GBUFFER_TEXTURE_TYPE_POSITION);
			glBlitFramebuffer(0, 0, width, height, 0, halfHeight, halfWidth, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

			setReadBuffer(GBUFFER_TEXTURE_TYPE_NORMAL);
			glBlitFramebuffer(0, 0, width, height, halfWidth, halfHeight, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

			setReadBuffer(GBUFFER_TEXTURE_TYPE_ALBEDO);
			glBlitFramebuffer(0, 0, width, height, 0, 0, halfWidth, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

			setReadBuffer(GBUFFER_TEXTURE_TYPE_SPECULAR);
			glBlitFramebuffer(0, 0, width, height, halfWidth, 0, width, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		}
	}
}
