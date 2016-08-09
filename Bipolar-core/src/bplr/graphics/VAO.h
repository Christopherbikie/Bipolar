#pragma once

#include <GL/glew.h>
#include "VBO.h"
#include <map>
#include "Shader.h"

namespace bplr
{
	namespace graphics
	{
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
