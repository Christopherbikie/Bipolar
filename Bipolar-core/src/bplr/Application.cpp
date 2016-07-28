#define GLEW_STATIC

#include <GL/glew.h>
#include <glfw3.h>
#include <iostream>
#include <string>
#include "Application.h"

namespace bplr
{
	Bipolar::Bipolar()
	{
	}

	int Bipolar::init(int width, int height)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		m_window = glfwCreateWindow(width, height, "Bipolar", nullptr, nullptr);
		if (m_window == nullptr)
		{
			std::cout << "Failed to create the GLFW m_window" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(m_window);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialise GLEW" << std::endl;
			return -1;
		}

		glfwGetFramebufferSize(m_window, &m_width, &m_height);
		glViewport(0, 0, m_width, m_height);
		glEnable(GL_DEPTH_TEST);

		return 0;
	}

	void Bipolar::update()
	{
		glfwPollEvents();
	}

	void Bipolar::render()
	{
		glClearColor(0.3f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(m_window);
	}

	void Bipolar::cleanUp()
	{
		glfwTerminate();
	}

	bool Bipolar::isCloseRequested() const
	{
		return glfwWindowShouldClose(m_window) == GL_FALSE ? false : true;
	}
}
		