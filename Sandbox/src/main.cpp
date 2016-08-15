#include <iostream>
#include <string>
#include "Bipolar.h"

int main()
{
	using namespace bplr;

	// INIT ----------------------------------------

	Bipolar* engine = new Bipolar();

	if (engine->init() != 0)
		return -1;

	graphics::window* window = engine->createWindow("Bipolar", 1024, 576);

	if (engine->initGlew() != 0)
		return -1;

	// Prepare vertices
	GLfloat vertices[] = {
		-1.0f,	-1.0f,	1.0f,
		1.0f,	-1.0f,	1.0f,
		1.0f,	1.0f,	1.0f,
		-1.0f,	1.0f,	1.0f,
		-1.0f,	-1.0f,	-1.0f,
		1.0f,	-1.0f,	-1.0f,
		1.0f,	1.0f,	-1.0f,
		-1.0f,	1.0f,	-1.0f,
	};

	GLfloat colours[] = {
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
	};

	GLuint indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};

	// Create Shader
	graphics::Shader shader = graphics::Shader();
	shader.addSource(graphics::VERTEX_SHADER, "res/vertex.vert");
	shader.addSource(graphics::FRAGMENT_SHADER, "res/fragment.frag");
	shader.link();

	// Create VAO
	graphics::VAO vao = graphics::VAO();
	vao.storeInBuffer(&shader, "position", 3, sizeof(vertices) / sizeof(*vertices) / 3, vertices);
	vao.storeInBuffer(&shader, "colour", 3, sizeof(colours) / sizeof(*colours) / 3, colours);
	vao.storeInElementBuffer(sizeof(indices) / sizeof(*indices), indices);

	// Create Entity
	entity::Entity* triangle = (new entity::Entity())
		->addComponent(new entity::TransformComponent(math::vec3(0.0f, 0.0f, 0.0f)))
		->addComponent(new entity::MeshComponent(&vao));

	// Create projection matrix
	math::mat4 projectionMatrix = math::mat4::perspective(65.0f, 16.0f / 9.0f, 1.0f, 1000.0f);

	// Timing vars
	double previous = time::getTime();
	double lag = 0.0;
	double lastSecond = previous;
	long frames = 0;
	long updates = 0;

	// GAME LOOP ----------------------------------

	while (!engine->shouldApplicationClose())
	{
		// Timing math
		double current = time::getTime();
		double delta = current - previous;
		previous = current;
		lag += delta;

		// Input
		engine->getInput();

		// Update
		while (lag >= time::MS_PER_UPDATE)
		{
			// Transform cube
			triangle->getComponent<entity::TransformComponent>()->position = math::vec3(sin(current), cos(current), 0);
			triangle->getComponent<entity::TransformComponent>()->rotation = math::vec3(sin(current * 1.1f) * 120, cos(current * 1.4f) * 120, 0);
			triangle->getComponent<entity::TransformComponent>()->scale = math::vec3(sin(current * 1.5f) / 2 + 0.5f, cos(current) / 2 + 0.5f, sin(current * 1.3f) / 2 + 0.5f);

			engine->update();
			lag -= time::MS_PER_UPDATE;
			updates++;
		}

		// Load uniforms
		shader.loadUniform("transform", triangle->getComponent<entity::TransformComponent>()->getTransform());
		shader.loadUniform("view", math::mat4(1.0f).translate(-math::vec3(0.0f, 0.0f, 2.0)));
		shader.loadUniform("projection", projectionMatrix);

		// Render
		float colour = sin(current * 2) / 2 + 0.5f;
		window->setBackgroundColour(0.4f * colour, 0.2f * colour, 0.4f * colour, 1.0f);

		window->beginRender();
		triangle->getComponent<entity::MeshComponent>()->render(shader);
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
