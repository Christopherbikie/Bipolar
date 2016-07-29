#include <iostream>
#include <string>
#include "Bipolar.h"

int main()
{
	bplr::Bipolar* engine = new bplr::Bipolar();

	if (engine->init() != 0)
		return -1;

	bplr::window* window = engine->createWindow("Bipolar", 800, 600);;

	engine->createWindow("Bipolar 2", 800, 600);

	if (engine->initGlew() != 0)
		return -1;

	while (!engine->shouldApplicationClose())
	{
		engine->update();
		float colour = sin(glfwGetTime() * 2) / 2 + 0.5f;
		window->setBackgroundColour(0.4f * colour, 0.2f * colour, 0.4f * colour, 1.0f);
		engine->render();
	}

	delete engine;

	return 0;
}
