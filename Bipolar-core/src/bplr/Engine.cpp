#define GLEW_STATIC

#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include "Engine.h"
#include "graphics/Window.h"
#include "input/Mouse.h"
#include <vector>
#include "graphics/ModelStore.h"
#include "graphics/TextureStore.h"

namespace bplr
{
	std::vector<graphics::Window*> m_windows;
	bool isGlewInitialised = false;

	void terminateEngine()
	{
		for (graphics::Window* window : m_windows)
			delete window;
		graphics::modelStore->clear();
		graphics::TextureStore::clear();
		glfwTerminate();
	}

	int init()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		return 0;
	}

	int initGlew()
	{
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialise GLEW" << std::endl;
			return -1;
		}
		isGlewInitialised = true;
		return 0;
	}

	graphics::Window* createWindow(std::string name, int width, int height)
	{
		graphics::Window* window = new graphics::Window(name, width, height);
		m_windows.push_back(window);
		if (!isGlewInitialised)
			initGlew();
		return window;
	}

	void getInput()
	{
		input::Mouse::update();
		glfwPollEvents();
	}

	void processCloseRequests()
	{
		for (int i = 0; i < m_windows.size(); ++i)
			if (m_windows[i]->isCloseRequested())
			{
				delete m_windows[i];
				m_windows.erase(m_windows.begin() + i);
			}
	}

	bool shouldApplicationClose()
	{
		return m_windows.size() > 0 ? false : true;
	}
}
		