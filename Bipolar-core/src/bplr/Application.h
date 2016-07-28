#pragma once

#include <glfw3.h>

namespace bplr
{
	class Bipolar
	{
	public:
		Bipolar();

		int init(int width, int height);
		void update();
		void render();
		void cleanUp();

		bool isCloseRequested() const;

	private:
		GLFWwindow* m_window;
		int m_width, m_height;
	};
}
