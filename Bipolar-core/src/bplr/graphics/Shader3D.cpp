#include "Shader3D.h"

namespace bplr
{
	namespace graphics
	{
		void Shader3D::drawArrays(GLint first, GLint count) const
		{
			glDrawArrays(GL_TRIANGLES, first, count);
		}

		void Shader3D::drawElements(GLint count)
		{
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
		}
	}
}
