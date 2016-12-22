#pragma once

#include "Texture.h"

namespace bplr
{
	namespace graphics
	{
		class GBuffer
		{
		public:
			enum GBufferTextureType
			{
				GBUFFER_TEXTURE_TYPE_POSITION,
				GBUFFER_TEXTURE_TYPE_NORMAL,
				GBUFFER_TEXTURE_TYPE_ALBEDO,
				GBUFFER_TEXTURE_TYPE_SPECULAR,
				GBUFFER_NUM_TEXURES,
			};

			GBuffer();
			~GBuffer();

			void init(GLuint width, GLuint height);

			void bindForReading() const;
			void bindForWriting() const;
			void setReadBuffer(GBufferTextureType buffer) const;

			void clear() const;

			void drawBuffers(GLsizei width, GLsizei height) const;

		private:
			GLuint m_location;
			GLuint m_textures[GBUFFER_NUM_TEXURES];
			GLuint m_depthTexture;
		};
	}
}
