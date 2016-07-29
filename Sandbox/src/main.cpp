#include <iostream>
#include <string>
#include "Bipolar.h"

int main()
{
	// INIT ----------------------------------------

	bplr::Bipolar* engine = new bplr::Bipolar();

	if (engine->init() != 0)
		return -1;

	bplr::window* window = engine->createWindow("Bipolar", 800, 600);;

	if (engine->initGlew() != 0)
		return -1;

	// Timing vars
	double previous = bplr::time::getTime();
	double lag = 0.0;
	double lastSecond = previous;
	long frames = 0;
	long updates = 0;

	// GAME LOOP ----------------------------------

	while (!engine->shouldApplicationClose())
	{
		// Timing math
		double current = bplr::time::getTime();
		double delta = current - previous;
		previous = current;
		lag += delta;

		// Input
		engine->getInput();

		// Update
		while (lag >= bplr::time::MS_PER_UPDATE)
		{
			engine->update();
			lag -= bplr::time::MS_PER_UPDATE;
			updates++;
		}

		// Render
		float colour = sin(current * 2) / 2 + 0.5f;
		window->setBackgroundColour(0.4f * colour, 0.2f * colour, 0.4f * colour, 1.0f);
		engine->render();
		frames++;

		// Update FPS / UPS
		if (current - lastSecond >= 1)
		{
			window->setTitle("Bipolar :: FPS: " + std::to_string(frames) + " UPS: " + std::to_string(updates));
			lastSecond = current;
			frames = 0;
			updates = 0;
		}

		// Close windows
		engine->processCloseRequests();
	}

	// CLEAN UP -----------------------------------

	delete engine;

	return 0;
}
