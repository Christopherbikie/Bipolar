#include "Keyboard.h"

namespace bplr
{
	namespace input
	{
		void Keyboard::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
		{
			if (key >= 0 && key < 1024)
			{
				if (action == GLFW_PRESS)
					m_keys[key] = true;
				else if (action == GLFW_RELEASE)
					m_keys[key] = false;
			}
			if (action == GLFW_PRESS)
				for (KeyEventHandler* handler : m_keyHandlers[key])
					handler->pressKey(key);
		}

		bool Keyboard::isKeyDown(int key)
		{
			return m_keys[key];
		}

		void Keyboard::addKeyHandler(GLuint key, KeyEventHandler* handler)
		{
			m_keyHandlers[key].push_back(handler);
		}

		bool Keyboard::m_keys[1024];

		std::map<GLuint, std::vector<KeyEventHandler*>> Keyboard::m_keyHandlers;
	}
}
