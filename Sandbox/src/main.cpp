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
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};
	GLuint indices[] = {
		0,1,3,
		3,1,2
	};
	GLfloat textureCoords[] = {
		0,0,
		0,1,
		1,1,
		1,0
	};

	// Load textures
	graphics::Texture* texture1 = new graphics::Texture("res/images/test.png");
	graphics::Texture* texture2 = new graphics::Texture("res/images/wall.jpg");

	// Create Shader
	graphics::Shader shader = graphics::Shader();
	shader.addSource(graphics::VERTEX_SHADER, "res/shaders/vertex.vert");
	shader.addSource(graphics::FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader.link();

	// Create VAO
	graphics::VAO vao = graphics::VAO();
	vao.storeInBuffer(&shader, "position", 3, sizeof(vertices) / sizeof(*vertices) / 3, vertices);
	vao.storeInBuffer(&shader, "textureCoords", 2, sizeof(textureCoords) / sizeof(*textureCoords) / 2, textureCoords);
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
			engine->update();
			lag -= time::MS_PER_UPDATE;
			updates++;
		}

		// Load uniforms
		shader.loadUniform("transform", triangle->getComponent<entity::TransformComponent>()->getTransform());
		shader.loadUniform("view", math::mat4(1.0f).translate(-math::vec3(0.0f, 0.0f, 1.0)));
		shader.loadUniform("projection", projectionMatrix);

		// Render
		float colour = sin(current * 2) / 2 + 0.5f;
		window->setBackgroundColour(0.4f * colour, 0.2f * colour, 0.4f * colour, 1.0f);

		window->beginRender();
		texture1->bind(&shader, "diffuseTexture1");
		texture2->bind(&shader, "diffuseTexture2");
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
	delete texture1;
	delete texture2;
	delete engine;

	return 0;
}
