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

		void VAO::storeInBuffer(GLuint location, GLuint componentsPerVertex, GLint vertexCount, GLfloat* data, DataUsage usage)
		{
			bind();
			
			glGenBuffers(1, &m_vbos[location]);
			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[location]);
			glBufferData(GL_ARRAY_BUFFER, vertexCount * componentsPerVertex * sizeof(GLfloat), data, static_cast<GLenum>(usage));

			glVertexAttribPointer(location, componentsPerVertex, GL_FLOAT, GL_FALSE, componentsPerVertex * sizeof(GLfloat), (GLvoid*) 0);
			glEnableVertexAttribArray(location);

			unbind();

			if (vertexCount > m_vertexCount)
				m_vertexCount = vertexCount;
		}

		void VAO::storeInElementBuffer(GLint vertexCount, GLuint* data, DataUsage usage)
		{
			bind();

			glGenBuffers(1, &m_ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexCount * sizeof(GLuint), data, usage);

			unbind();

			if (vertexCount > m_vertexCount)
				m_vertexCount = vertexCount;
		}

		void VAO::bindEBO() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		}

		GLuint VAO::getVertexCount() const
		{
			return m_vertexCount;
		}
	}
}
