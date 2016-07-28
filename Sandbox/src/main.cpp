#include <iostream>
#include <string>
#include "Bipolar.h"

int main()
{
	bplr::Bipolar engine = bplr::Bipolar();

	if (engine.init(800, 600) != 0)
		return -1;

	while (!engine.isCloseRequested())
	{
		engine.update();
		engine.render();
	}

	engine.cleanUp();

	return 0;
}
