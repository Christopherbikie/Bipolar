#pragma once
#include <glfw3.h>
#include "../graphics/Window.h"
#include "../math/vec2.h"

namespace bplr
{
	namespace input
	{
		class Mouse
		{
		public:
			static void mouseMoveCallback(GLFWwindow* window, double xPosition, double yPosition);

			static math::vec2 getPosition();
			static math::vec2 getMovement();

			static void setCaptured(graphics::Window* window, bool value);
			static void toggleCaptured(graphics::Window* window); 
			static bool isCaptured();

			static void update();

		private:
			static math::vec2 m_position;
			static math::vec2 m_difference;
			static bool m_captured;
		};
	}
}
