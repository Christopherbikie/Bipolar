#include "Framebuffer.h"
#include <iostream>

namespace bplr
{
	namespace graphics
	{
		Framebuffer::Framebuffer(bool enableDepthTest)
			: m_enableDepthTest(enableDepthTest)
		{
			glGenFramebuffers(1, &m_location);
			bind();

			m_texture = new Texture(1366, 768);
			glBindTexture(GL_TEXTURE_2D, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getLocation(), 0);

			glGenRenderbuffers(1, &m_renderBufferLocation);
			glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferLocation);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1366, 768);
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferLocation);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "Failed to complete framebuffer! GLenum " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;

			bindDefault();
		}

		Framebuffer::~Framebuffer()
		{
			glDeleteFramebuffers(1, &m_location);
		}

		void Framebuffer::bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_location);
			if (m_enableDepthTest)
				glEnable(GL_DEPTH_TEST);
			else
				glDisable(GL_DEPTH_TEST);
		}

		void Framebuffer::bindDefault()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void Framebuffer::bindTexture(Shader *shader, std::string uniformName) const
		{
			m_texture->bind(shader, uniformName.c_str());
		}

		void Framebuffer::setClearColour(math::vec3 colour)
		{
			m_clearColour = colour;
		}

		void Framebuffer::clear() const
		{
			if (m_enableDepthTest)
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			else
				glClear(GL_COLOR_BUFFER_BIT);
		}

		void Framebuffer::setEnableDepthTest(bool enable)
		{
			m_enableDepthTest = enable;
		}
	}
}
