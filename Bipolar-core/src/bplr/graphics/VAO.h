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

			void storeInBuffer(Shader *program, GLchar *attribName, GLuint componentsPerVertex, GLint vertexCount, GLfloat *data, DataUsage usage);
			void storeInBuffer(Shader *program, GLchar *attribName, GLuint componentsPerVertex, GLint vertexCount, GLfloat *data);

		private:
			GLuint m_location;
			std::map<GLint, VBO> m_vbos;
		};
	}
}
