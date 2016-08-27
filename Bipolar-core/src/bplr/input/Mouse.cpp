#include "Mouse.h"

namespace bplr
{
	namespace input
	{
		void Mouse::mouseMoveCallback(GLFWwindow* window, double xPosition, double yPosition)
		{
			math::vec2 newPosition = math::vec2(xPosition, yPosition);
			m_difference = newPosition - m_position;
			m_position = newPosition;
		}

		math::vec2 Mouse::getPosition()
		{
			return m_position;
		}

		math::vec2 Mouse::getMovement()
		{
			return m_difference;
		}

		void Mouse::setCaptured(graphics::window* window, bool value)
		{
			if (value)
				glfwSetInputMode(window->getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			else
				glfwSetInputMode(window->getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

			m_captured = value;
		}

		void Mouse::toggleCaptured(graphics::window* window)
		{
			setCaptured(window, !m_captured);
		}

		bool Mouse::isCaptured()
		{
			return m_captured;
		}

		void Mouse::update()
		{
			m_difference = math::vec2(0.0f);
		}

		math::vec2 Mouse::m_position;
		math::vec2 Mouse::m_difference;
		bool Mouse::m_captured = false;
	}
}
