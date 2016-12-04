#include "Shader2D.h"

namespace bplr
{
	namespace graphics
	{
		VAO* Shader2D::rectangleVAO = nullptr;
		GLboolean Shader2D::isGeometryInitialised = false;

		void Shader2D::postLink()
		{
			GLfloat vertices[] = {
				0.5f,  0.5f, 0.0f,  // Top Right
				0.5f, -0.5f, 0.0f,  // Bottom Right
				-0.5f, -0.5f, 0.0f,  // Bottom Left
				-0.5f,  0.5f, 0.0f,  // Top Left 
			};
			GLuint indices[] = {
				3, 1, 0,  // First Triangle
				3, 2, 1,  // Second Triangle
			};

			rectangleVAO = new VAO();
			rectangleVAO->bind();
			rectangleVAO->storeInBuffer(this, "position", 3, 4, vertices);
			rectangleVAO->storeInElementBuffer(6, indices);
			rectangleVAO->unbind();
		}

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
