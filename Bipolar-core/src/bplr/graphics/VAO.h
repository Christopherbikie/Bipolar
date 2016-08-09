#pragma once

#include <GL/glew.h>
#include <map>
#include "Shader.h"

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

			void storeInBuffer(Shader *program, GLchar *attribName, GLuint componentsPerVertex, GLint vertexCount, GLfloat *data, DataUsage usage = STATIC_DRAW);
			void storeInElementBuffer(GLint vertexCount, GLuint* data, DataUsage usage = STATIC_DRAW);
			void bindEBO();

		private:
			GLuint m_location;
			GLuint m_ebo;
			std::map<GLint, GLuint> m_vbos;
		};
	}
}
