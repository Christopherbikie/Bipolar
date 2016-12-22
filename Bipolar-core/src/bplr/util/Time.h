#pragma once

#include <glfw3.h>

namespace bplr
{
	class time
	{
	public:
		static constexpr float FRAME_CAP = 60.0f;
		static constexpr float MS_PER_UPDATE = 1 / FRAME_CAP;

		static GLfloat getTime()
		{
			return (GLfloat) glfwGetTime();
		}
	};
}
