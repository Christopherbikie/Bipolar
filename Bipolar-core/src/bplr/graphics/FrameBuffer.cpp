#include "Framebuffer.h"
#include <iostream>

namespace bplr
{
	namespace graphics
	{
		void bindDefaultFramebuffer()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void clearFramebuffer()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		Framebuffer::Framebuffer(GLsizei width, GLsizei height, GLuint numColorBuffers)
			: m_width(width), m_height(height)
		{
			GLint maxAttach = 0;
			glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttach);
			GLint maxDrawBuf = 0;
			glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuf);
			if (numColorBuffers > maxAttach)
			{
				std::cout << "Attempted to create a Framebuffer with more color attachments or draw buffers than the implementation allows." << std::endl
					<< "Attempted: " << numColorBuffers << " GL_MAX_COLOR_ATTACHMENTS: " << maxAttach << " GL_MAX_DRAW_BUFFERS: " << maxDrawBuf;
				return;
			}

			glGenFramebuffers(1, &m_location);
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_location);

			for (GLuint i = 0; i < numColorBuffers; ++i)
			{
				Texture* texture = new Texture(m_width, m_height, 32);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture->getLocation(), 0);
				m_textures.push_back(texture);
			}

			glGenTextures(1, &m_depthTexture);
			glBindTexture(GL_TEXTURE_2D, m_depthTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

			std::vector<GLenum> drawBuffers;
			for (int i = 0; i < numColorBuffers; ++i)
				drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + i);
			glDrawBuffers(numColorBuffers, drawBuffers.data());

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "Failed to complete framebuffer! GLenum " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;

			bindDefaultFramebuffer();
		}

		Framebuffer::~Framebuffer()
		{
			glDeleteFramebuffers(1, &m_location);
			for (Texture* texture : m_textures)
				delete texture;
			glDeleteTextures(1, &m_depthTexture);
		}

		void Framebuffer::bindForReading() const
		{
			glBindFramebuffer(GL_READ_FRAMEBUFFER, m_location);
		}

		void Framebuffer::bindForWriting() const
		{
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_location);
		}

		void Framebuffer::setReadBuffer(GLuint buffer) const
		{
			glReadBuffer(GL_COLOR_ATTACHMENT0 + buffer);
		}

		void Framebuffer::bindTexture(GLuint index, Shader* shader, std::string uniformName) const
		{
			m_textures[index]->bind(shader, uniformName.c_str());
		}

		void Framebuffer::clear() const
		{
			clearFramebuffer();
		}

		void Framebuffer::drawBuffers() const
		{
			size_t numberOfTextures = m_textures.size();

			if (numberOfTextures == 1)
			{
				setReadBuffer(0);
				glBlitFramebuffer(0, 0, m_width, m_height, 0, m_height, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
			}
			else if (numberOfTextures <= 4)
			{
				GLsizei halfWidth = (GLsizei)(m_width / 2.0f);
				GLsizei halfHeight = (GLsizei)(m_height / 2.0f);

				switch (numberOfTextures)
				{
				case 4:
					setReadBuffer(3);
					glBlitFramebuffer(0, 0, m_width, m_height, halfWidth, 0, m_width, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				case 3:
					setReadBuffer(2);
					glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, halfWidth, halfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				case 2:
					setReadBuffer(1);
					glBlitFramebuffer(0, 0, m_width, m_height, halfWidth, halfHeight, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
					setReadBuffer(0);
					glBlitFramebuffer(0, 0, m_width, m_height, 0, halfHeight, halfWidth, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				}
			}
			else if (numberOfTextures <= 9)
			{
				GLsizei oneThirdWidth = (GLsizei)(m_width / 3.0f);
				GLsizei twoThirdWidth = (GLsizei)(oneThirdWidth * 2.0f);
				GLsizei oneThirdHeight = (GLsizei)(m_height / 3.0f);
				GLsizei twoThirdHeight = (GLsizei)(oneThirdHeight * 2.0f);

				switch (numberOfTextures)
				{
				case 9:
					setReadBuffer(8);
					glBlitFramebuffer(0, 0, m_width, m_height, twoThirdWidth, 0, m_width, oneThirdHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				case 8:
					setReadBuffer(7);
					glBlitFramebuffer(0, 0, m_width, m_height, oneThirdWidth, 0, twoThirdWidth, oneThirdHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				case 7:
					setReadBuffer(6);
					glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, oneThirdWidth, oneThirdHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				case 6:
					setReadBuffer(5);
					glBlitFramebuffer(0, 0, m_width, m_height, twoThirdWidth, oneThirdHeight, m_width, twoThirdHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				case 5:
					setReadBuffer(4);
					glBlitFramebuffer(0, 0, m_width, m_height, oneThirdWidth, oneThirdHeight, twoThirdWidth, twoThirdHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
					setReadBuffer(3);
					glBlitFramebuffer(0, 0, m_width, m_height, 0, oneThirdHeight, oneThirdWidth, twoThirdHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
					setReadBuffer(2);
					glBlitFramebuffer(0, 0, m_width, m_height, twoThirdWidth, twoThirdHeight, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
					setReadBuffer(1);
					glBlitFramebuffer(0, 0, m_width, m_height, oneThirdWidth, twoThirdHeight, twoThirdWidth, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
					setReadBuffer(0);
					glBlitFramebuffer(0, 0, m_width, m_height, 0, twoThirdHeight, oneThirdWidth, m_height, GL_COLOR_BUFFER_BIT, GL_LINEAR);
				}
			}
		}
	}
}
