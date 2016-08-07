#define GLEW_STATIC

#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include "Application.h"
#include "graphics/Window.h"

namespace bplr
{
	Bipolar::Bipolar()
	{
	}

	Bipolar::~Bipolar()
	{
		for (graphics::window* window : m_windows)
			delete window;
		glfwTerminate();
	}

	int Bipolar::init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		return 0;
	}

	int Bipolar::initGlew()
	{
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialise GLEW" << std::endl;
			return -1;
		}
		return 0;
	}

	graphics::window* Bipolar::createWindow(std::string name, int width, int height)
	{
		graphics::window* window = new graphics::window(name, width, height);
		m_windows.push_back(window);
		return window;
	}

	void Bipolar::getInput()
	{
		glfwPollEvents();
	}

	void Bipolar::update()
	{
	}

	void Bipolar::processCloseRequests()
	{
		for (int i = 0; i < m_windows.size(); ++i)
			if (m_windows[i]->isCloseRequested())
			{
				delete m_windows[i];
				m_windows.erase(m_windows.begin() + i);
			}
	}

	bool Bipolar::shouldApplicationClose() const
	{
		return m_windows.size() > 0 ? false : true;
	}
}
		