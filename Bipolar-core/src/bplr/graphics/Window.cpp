#include "Window.h"
#include <iostream>
#include "../input/Keyboard.h"
#include "../input/Mouse.h"

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

			glEnable(GL_DEPTH_TEST);

			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glFrontFace(GL_CCW);

			glfwSwapInterval(1);

			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, 1);
			glfwSetKeyCallback(m_window, input::Keyboard::keyCallback);
			glfwSetCursorPosCallback(m_window, input::Mouse::mouseMoveCallback);
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
