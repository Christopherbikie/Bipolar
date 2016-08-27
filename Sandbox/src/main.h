#pragma once

#include "Bipolar.h"

bplr::graphics::Window* m_window;

int main();

class MouseCaptureHandler : bplr::input::KeyEventHandler
{
public:
	void pressKey(GLuint key) override;
};
