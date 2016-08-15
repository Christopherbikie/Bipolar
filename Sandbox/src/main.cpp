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


	// Prepare vertices
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

	// Create Shader
	bplr::graphics::Shader shader = bplr::graphics::Shader();
	shader.addSource(bplr::graphics::VERTEX_SHADER, "res/vertex.vert");
	shader.addSource(bplr::graphics::FRAGMENT_SHADER, "res/fragment.frag");
	shader.link();

	// Create VAO
	bplr::graphics::VAO vao = bplr::graphics::VAO();
	vao.storeInBuffer(&shader, "position", 3, sizeof(vertices) / sizeof(*vertices) / 3, vertices);
	vao.storeInBuffer(&shader, "colour", 3, sizeof(colours) / sizeof(*colours) / 3, colours);
	vao.storeInElementBuffer(sizeof(indices) / sizeof(*indices), indices);

	// Create Entity
	bplr::entity::Entity* triangle = (new bplr::entity::Entity())
		->addComponent(new bplr::entity::MeshComponent(&vao));

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

		window->beginRender();
		triangle->getComponent<bplr::entity::MeshComponent>()->render(shader);
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

	delete triangle;
	delete engine;

	return 0;
}
