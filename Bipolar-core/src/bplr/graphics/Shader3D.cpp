#include "Shader3D.h"

namespace bplr
{
	namespace graphics
	{
		void Shader3D::drawArrays(GLint first, GLint count, GLenum primitiveType) const
		{
			glDrawArrays(primitiveType, first, count);
		}

		void Shader3D::drawElements(GLint count, GLenum primitiveType) const
		{
			glDrawElements(primitiveType, count, GL_UNSIGNED_INT, 0);
		}
	}
}
