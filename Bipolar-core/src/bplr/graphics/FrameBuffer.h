#pragma once

#include <GL/glew.h>
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
			Framebuffer();
			~Framebuffer();

			void bind() const;

			void bindTexture(Shader *shader, std::string uniformName) const;

			void clear() const;

		private:
			GLuint m_location;
			GLuint m_renderBufferLocation;
			Texture* m_texture;
		};
	}
}
