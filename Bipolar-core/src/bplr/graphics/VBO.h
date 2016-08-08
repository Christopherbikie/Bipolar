#pragma once

#include <GL/glew.h>

namespace bplr
{
	namespace graphics
	{
		enum DataUsage
		{
			STATIC_DRAW = GL_STATIC_DRAW,
			DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
			STREAM_DRAW = GL_STREAM_DRAW,
		};

		class VBO
		{
		public:
			VBO();
			VBO(GLfloat data[], GLint dataSize, DataUsage usage);
			~VBO();
			
			void store(GLfloat data[], GLint dataCount, DataUsage usage) const;
			GLuint getLocation() const;

		private:
			GLuint m_location;
		};
	}
}
