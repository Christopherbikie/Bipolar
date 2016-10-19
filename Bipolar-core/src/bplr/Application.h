#pragma once

#include <vector>
#include "graphics/layers/Layer.h"
#include "graphics/Window.h"

namespace bplr
{
	class Application
	{
	public:
		Application(std::string title, int width, int height);
		~Application();

		void addLayer(graphics::Layer* layer);

		void start();

	protected:
		std::vector<graphics::Layer*> m_layers;
		graphics::Window* m_window;
	};
}
