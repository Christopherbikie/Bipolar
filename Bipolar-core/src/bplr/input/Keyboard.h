#pragma once

#include "glfw3.h"
#include <map>
#include <vector>

namespace bplr
{
	namespace input
	{
		class KeyEventHandler
		{
		public:
			virtual ~KeyEventHandler()
			{
			}

			virtual void pressKey(GLuint key) = 0;
		};

		class Keyboard
		{
		public:
			static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
			static bool isKeyDown(int key);
			static void addKeyHandler(GLuint key, KeyEventHandler* handler);
			static void releaseAllKeys();

		private:
			static bool m_keys[1024];

			static std::map<GLuint, std::vector<KeyEventHandler*>> m_keyHandlers;
		};
	}
}
