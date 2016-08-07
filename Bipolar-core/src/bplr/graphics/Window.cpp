#include "Window.h"
#include <iostream>

namespace bplr
{
	namespace graphics
	{
		window::window(std::string title, int width, int height)
		{
			m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
			if (m_window == nullptr)
			{
				std::cout << "Failed to create the window \"" + title + "\"" << std::endl;
				glfwTerminate();
			}

			glfwMakeContextCurrent(m_window);

			glfwGetFramebufferSize(m_window, &m_width, &m_height);
			glViewport(0, 0, m_width, m_height);

			glfwSwapInterval(1);
		}

		window::~window()
		{
			glfwDestroyWindow(m_window);
		}


		void window::setBackgroundColour(float r, float g, float b, float a)
		{
			this->m_bgr = r;
			this->m_bgg = g;
			this->m_bgb = b;
			this->m_bga = a;
		}

		void window::setTitle(std::string title) const
		{
			glfwSetWindowTitle(m_window, title.c_str());
		}

		void window::beginRender() const
		{
			glfwMakeContextCurrent(m_window);

			glClearColor(m_bgr, m_bgg, m_bgb, m_bga);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void window::swapBuffers() const
		{
			glfwSwapBuffers(m_window);
		}

		GLFWwindow* window::getGLFWwindow() const
		{
			return m_window;
		}

		bool window::isCloseRequested() const
		{
			return glfwWindowShouldClose(m_window) == GL_FALSE ? false : true;
		}
	}
}
