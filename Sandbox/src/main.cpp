#include <string>
#include "Bipolar.h"

int main()
{
	using namespace bplr;

	// INIT ----------------------------------------

	Bipolar* engine = new Bipolar();

	if (engine->init() != 0)
		return -1;

	graphics::window* window = engine->createWindow("Bipolar", 1366, 768);

	if (engine->initGlew() != 0)
		return -1;

	// Create Shader
	graphics::Shader* shader = new graphics::Shader();
	shader->addSource(graphics::VERTEX_SHADER, "res/shaders/vertex.vert");
	shader->addSource(graphics::FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader->link();

	// Create Entity
	entity::Entity* entity = (new entity::Entity())
		->addComponent(new entity::TransformComponent(math::vec3(0.0f, 0.0f, 0.0f)))
		->addComponent(new entity::MeshComponent("res/models/cube.obj"));

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
			engine->update();
			lag -= time::MS_PER_UPDATE;
			updates++;
		}

		// Rotate entity
		entity->getComponent<entity::TransformComponent>()->rotation = math::vec3(sin(current) * 180, sin(current * 1.3f) * 180, sin(current * 0.8f) * 180);

		// Load uniforms
		shader->loadUniform("transform", entity->getComponent<entity::TransformComponent>()->getTransform());
		shader->loadUniform("view", math::mat4(1.0f).translate(-math::vec3(0.0f, 0.0f, 2.0)));
		shader->loadUniform("projection", projectionMatrix);

		// Render
		float colour = sin(current * 2) / 2 + 0.5f;
		window->setBackgroundColour(0.4f * colour, 0.2f * colour, 0.4f * colour, 1.0f);

		window->beginRender();
		entity->getComponent<entity::MeshComponent>()->render(shader);
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

	delete entity;
	delete shader;
	delete engine;

	return 0;
}
