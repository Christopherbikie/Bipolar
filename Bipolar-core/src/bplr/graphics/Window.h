#pragma once

#include <glfw3.h>
#include <string>

namespace bplr
{
	class window
	{
	public:
		window(std::string name, int width, int height);
		~window();

		void setBackgroundColour(float r, float g, float b, float a);
		void render() const;
		
		GLFWwindow* getGLFWwindow() const;
		bool isCloseRequested() const;

	private:
		GLFWwindow* m_window;
		int m_width, m_height;
		// Background clear colours
		float m_bgr = 0, m_bgg = 0, m_bgb = 0, m_bga = 1;
	};
}
