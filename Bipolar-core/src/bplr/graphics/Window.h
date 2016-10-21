#pragma once

#include <glfw3.h>
#include "../math/vec4.h"
#include "../math/vec3.h"

namespace bplr
{
	namespace graphics
	{
		class Window
		{
		public:
			Window(std::string title, int width, int height);
			~Window();

			void beginRender() const;
			void swapBuffers() const;

			void setBackgroundColour(math::vec4 colour);
			void setBackgroundColour(math::vec3 colour);
			void setTitle(std::string title) const;

			GLFWwindow* getGLFWwindow() const;
			bool isCloseRequested() const;

			int getWidth() const;
			int getHeight() const;

		private:
			GLFWwindow* m_window;
			int m_width, m_height;
			math::vec4 m_backgroundColour;
		};
	}
}
