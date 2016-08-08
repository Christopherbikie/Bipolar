#include "VBO.h"
#include <GL/glew.h>
#include <iostream>

namespace bplr
{
	namespace graphics
	{
		VBO::VBO()
		{
			glGenBuffers(1, &m_location);
		}

		VBO::VBO(GLfloat data[], GLint dataSize, DataUsage usage)
			: VBO()
		{
			store(data, dataSize, usage);
		}

		VBO::~VBO()
		{
			glDeleteBuffers(1, &m_location);
		}

		void VBO::store(GLfloat data[], GLint dataCount, DataUsage usage) const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_location);
			glBufferData(GL_ARRAY_BUFFER, dataCount * sizeof(GLfloat), data, static_cast<GLenum>(usage));
		}

		GLuint VBO::getLocation() const
		{
			return m_location;
		}
	}
}
