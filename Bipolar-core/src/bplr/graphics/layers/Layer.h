#pragma once

#include "../Window.h"

namespace bplr
{
	namespace graphics
	{
		class Layer
		{
		protected:
			Window* m_window;
			GLboolean m_visible = true;

		public:
			Layer();
			virtual ~Layer();

			virtual void init(Window* window);
			virtual void getInput();
			virtual void update(GLfloat delta);
			virtual void render();

			bool isVisible() const;
			void setVisible(GLboolean visible);

			Window* getWindow() const;
		};
	}
}
