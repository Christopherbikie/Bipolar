#pragma once

#include "VAO.h"

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
			
			glGenBuffers(1, &m_vbos[location]);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[location]);
			glBufferData(GL_ARRAY_BUFFER, vertexCount * componentsPerVertex * sizeof(GLfloat), data, static_cast<GLenum>(usage));

			glVertexAttribPointer(location, componentsPerVertex, GL_FLOAT, GL_FALSE, componentsPerVertex * sizeof(GLfloat), (GLvoid*) 0);
			glEnableVertexAttribArray(location);

			unbind();
		}

		void VAO::storeInElementBuffer(GLint vertexCount, GLuint* data, DataUsage usage)
		{
			bind();

			glGenBuffers(1, &m_ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(GLuint), data, usage);

			unbind();
		}

		void VAO::bindEBO()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		}
	}
}
