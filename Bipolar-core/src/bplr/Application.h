#pragma once

#include <glfw3.h>
#include <vector>

#include "graphics/Window.h"

namespace bplr
{
	class Bipolar
	{
	public:
		Bipolar();
		~Bipolar();

		static int init();
		static int initGlew();

		void getInput();
		void update();
		void processCloseRequests();

		graphics::Window* createWindow(std::string name, int width, int height);
		bool shouldApplicationClose() const;
		std::vector<graphics::Window*> getWindows() const;

	private:
		std::vector<graphics::Window*> m_windows;
		GLFWwindow* m_window;
		int m_width, m_height;
	};
}
