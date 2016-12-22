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
			Framebuffer(bool enableDepthTest = true);
			~Framebuffer();

			void bind() const;

			void bindTexture(Shader *shader, std::string uniformName) const;

			void setClearColour(math::vec3 colour);
			void clear() const;
			void setEnableDepthTest(bool enable);

		private:
			GLuint m_location;
			GLuint m_renderBufferLocation;
			Texture* m_texture;
			math::vec3 m_clearColour = math::vec3(0.0f);
			bool m_enableDepthTest;
		};
	}
}
