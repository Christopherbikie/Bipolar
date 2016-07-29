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
		void update();
		void render() const;

		bplr::window* createWindow(std::string name, int width, int height);
		bool shouldApplicationClose() const;
		std::vector<bplr::window*> getWindows() const;

	private:
		std::vector<bplr::window*> m_windows;
		GLFWwindow* m_window;
		int m_width, m_height;
	};
}
