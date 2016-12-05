#pragma once

#include <GL/glew.h>
#include <map>

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

		class VAO
		{
		public:
			VAO();
			~VAO();

			void bind() const;
			static void unbind();

			void storeInBuffer(GLuint location, GLuint componentsPerVertex, GLint vertexCount, GLfloat *data, DataUsage usage = STATIC_DRAW);
			void storeInElementBuffer(GLint vertexCount, GLuint* data, DataUsage usage = STATIC_DRAW);
			void bindEBO() const;

			GLuint getVertexCount() const;

		private:
			GLuint m_location;
			GLuint m_ebo;
			std::map<GLint, GLuint> m_vbos;
			GLuint m_vertexCount = 0;
		};
	}
}
