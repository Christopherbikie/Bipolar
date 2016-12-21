#include "Shader2D.h"

namespace bplr
{
	namespace graphics
	{
		void Shader2D::drawRect() const
		{
			use();
			rectangleVAO->bind();
			rectangleVAO->bindEBO();
			glDrawElements(GL_TRIANGLES, rectangleVAO->getVertexCount(), GL_UNSIGNED_INT, 0);
			rectangleVAO->unbind();
		}
	}
}
