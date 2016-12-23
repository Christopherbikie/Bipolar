#pragma once

#include "Texture.h"

namespace bplr
{
	namespace graphics
	{
		class GBuffer
		{
		public:
			GBuffer();
			~GBuffer();

			void init(GLsizei width, GLsizei height, GLuint numColorBuffers);

			void bindForReading() const;
			void bindForWriting() const;
			void setReadBuffer(GLuint bufferIndex) const;

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
