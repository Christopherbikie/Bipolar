#include "Application.h"
#include "Engine.h"
#include "util/Time.h"

namespace bplr
{
	Application::Application(std::string title, int width, int height)
	{
		bplr::init();
		
		m_window = createWindow(title, width, height);
	}

	Application::~Application()
	{
		// Don't delete m_window because it is handled automaticly by processCloseRequests in Engine.cpp

		for (graphics::Layer* layer : m_layers)
			delete layer;

		terminateEngine();
	}

	void Application::addLayer(graphics::Layer* layer)
	{
		layer->init(m_window);
		m_layers.push_back(layer);
	}

	void Application::start()
	{
		// Timing vars
		double previous = time::getTime();
		double lag = 0.0;
		double lastSecond = previous;
		long frames = 0;
		long updates = 0;

		while (!shouldApplicationClose())
		{
			// Timing math
			double current = time::getTime();
			double delta = current - previous;
			previous = current;
			lag += delta;

			// Get input
			bplr::getInput();
			for (graphics::Layer* layer : m_layers)
				layer->getInput();

			// Update
			while (lag >= time::MS_PER_UPDATE)
			{
				for (graphics::Layer* layer : m_layers)
					layer->update(delta);
				lag -= time::MS_PER_UPDATE;
				updates++;
			}

			// Render
			m_window->beginRender();
			for (graphics::Layer* layer : m_layers)
				if (layer->isVisible())
					layer->render();
			m_window->swapBuffers();
			frames++;

			// Check if we need to close any windows
			processCloseRequests();
		}
	}
}
