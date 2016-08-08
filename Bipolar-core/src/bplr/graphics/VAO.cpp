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

		void VAO::storeInBuffer(Shader *program, GLchar *attribName, GLuint componentsPerVertex, GLint vertexCount, GLfloat *data, DataUsage usage)
		{
			GLint location = glGetAttribLocation(program->getLocation(), attribName);

			bind();
			
			m_vbos[location].store(data, vertexCount * componentsPerVertex, usage);
			glVertexAttribPointer(location, componentsPerVertex, GL_FLOAT, GL_FALSE, componentsPerVertex * sizeof(GLfloat), (GLvoid*) 0);
			glEnableVertexAttribArray(location);

			unbind();
		}

		void VAO::storeInBuffer(Shader *program, GLchar *attribName, GLuint componentsPerVertex, GLint vertexCount, GLfloat *data)
		{
			storeInBuffer(program, attribName, componentsPerVertex,vertexCount , data, STATIC_DRAW);
		}
	}
}
