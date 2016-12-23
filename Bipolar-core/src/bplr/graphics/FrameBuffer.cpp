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

		Framebuffer::Framebuffer()
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

			bindDefaultFramebuffer();
		}

		Framebuffer::~Framebuffer()
		{
			glDeleteFramebuffers(1, &m_location);
		}

		void Framebuffer::bind() const
		{
			glBindFramebuffer(GL_FRAMEBUFFER, m_location);
		}

		void Framebuffer::bindTexture(Shader *shader, std::string uniformName) const
		{
			m_texture->bind(shader, uniformName.c_str());
		}

		void Framebuffer::clear() const
		{
			clearFramebuffer();
		}
	}
}
