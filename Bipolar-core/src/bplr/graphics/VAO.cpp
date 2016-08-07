#pragma once

#include "VAO.h"
#include <iostream>

namespace bplr
{
	namespace graphics
	{
		VAO::VAO()
		{
			glGenVertexArrays(1, &m_location);
		}

		VAO::~VAO()
		{
			glDeleteVertexArrays(1, &m_location);
		}

		void VAO::bind() const
		{
			glBindVertexArray(m_location);
		}

		void VAO::unbind()
		{
			glBindVertexArray(0);
		}

		void VAO::storeInBuffer(Shader *program, GLchar* name, GLuint size, GLfloat *data, GLint dataCount, DataUsage usage)
		{
			GLint location = glGetAttribLocation(program->getLocation(), name);

			bind();
			
			m_vbos[location].store(data, dataCount, usage);
			glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, size * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(location);

			unbind();
		}
	}
}
