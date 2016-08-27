#include "Window.h"
#include <iostream>
#include "../input/Keyboard.h"
#include "../input/Mouse.h"

namespace bplr
{
	namespace graphics
	{
		Window::Window(std::string title, int width, int height)
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

		Window::~Window()
		{
			glfwDestroyWindow(m_window);
		}

		void Window::setTitle(std::string title) const
		{
			glfwSetWindowTitle(m_window, title.c_str());
		}

		void Window::beginRender() const
		{
			glfwMakeContextCurrent(m_window);

			glClearColor(m_backgroundColour.x, m_backgroundColour.y, m_backgroundColour.z, m_backgroundColour.w);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::swapBuffers() const
		{
			glfwSwapBuffers(m_window);
		}

		void Window::setBackgroundColour(math::vec4 colour)
		{
			m_backgroundColour = colour;
		}

		void Window::setBackgroundColour(math::vec3 colour)
		{
			m_backgroundColour = math::vec4(colour, 1.0f);
		}

		GLFWwindow* Window::getGLFWwindow() const
		{
			return m_window;
		}

		bool Window::isCloseRequested() const
		{
			return glfwWindowShouldClose(m_window) == GL_FALSE ? false : true;
		}
	}
}
