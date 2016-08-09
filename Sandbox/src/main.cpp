#include <iostream>
#include <string>
#include "Bipolar.h"

int main()
{
	// INIT ----------------------------------------

	bplr::Bipolar* engine = new bplr::Bipolar();

	if (engine->init() != 0)
		return -1;

	bplr::graphics::window* window = engine->createWindow("Bipolar", 800, 600);;

	if (engine->initGlew() != 0)
		return -1;

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	GLfloat colours[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 2
	};

	bplr::graphics::Shader shader = bplr::graphics::Shader();
	shader.addSource(bplr::graphics::VERTEX_SHADER, "res/vertex.vert");
	shader.addSource(bplr::graphics::FRAGMENT_SHADER, "res/fragment.frag");
	shader.link();

	bplr::graphics::VAO vao = bplr::graphics::VAO();
	vao.storeInBuffer(&shader, "position", 3, sizeof(vertices) / sizeof(*vertices) / 3, vertices);
	vao.storeInBuffer(&shader, "colour", 3, sizeof(colours) / sizeof(*colours) / 3, colours);
	vao.storeInElementBuffer(sizeof(indices) / sizeof(*indices), indices);

//	GLuint ebo;
//	glGenBuffers(1, &ebo);
//	vao.bind();
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//	vao.unbind();

	// Timing vars
	double previous = bplr::time::getTime();
	double lag = 0.0;
	double lastSecond = previous;
	long frames = 0;
	long updates = 0;

//	bplr::math::mat4 projection = bplr::math::mat4().orthographic(-10, 10, -10, 10, 0.01f, 1000.0f);
//	bplr::math::vec3 coord = bplr::math::vec3(3, 3, -1);
//	std::cout << projection * coord << std::endl;

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

		window->beginRender();
		shader.use();
		vao.bind();
		vao.bindEBO();
		shader.drawElements(3);
		vao.unbind();
		window->swapBuffers();
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
