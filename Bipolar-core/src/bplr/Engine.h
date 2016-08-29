#pragma once

#include "graphics/Window.h"

namespace bplr
{
	int init();

	void getInput();
	graphics::Window* createWindow(std::string name, int width, int height);

	void processCloseRequests();
	bool shouldApplicationClose();
	void terminateEngine();
}
