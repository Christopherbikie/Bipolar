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

			void storeInBuffer(Shader *program, GLchar* name, GLuint size, GLfloat *data, GLint dataCount, DataUsage usage);

		private:
			GLuint m_location;
			std::map<GLint, VBO> m_vbos;
		};
	}
}
