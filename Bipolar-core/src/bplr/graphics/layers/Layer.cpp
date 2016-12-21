#include "Layer.h"

namespace bplr
{
	namespace graphics
	{
		Layer::Layer()
		{
		}

		Layer::~Layer()
		{
		}

		void Layer::init(Window* window)
		{
			m_window = window;
		}

		void Layer::getInput()
		{
		}

		void Layer::update(GLfloat delta)
		{
		}

		void Layer::render()
		{
		}

		bool Layer::isVisible() const
		{
			return m_visible;
		}

		void Layer::setVisible(GLboolean visible)
		{
			m_visible = visible;
		}

		Window* Layer::getWindow() const
		{
			return m_window;
		}
	}
}
