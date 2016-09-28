#include "main.h"

int main()
{
	using namespace bplr;

	// INIT ----------------------------------------

	if (init() != 0)
		return -1;

	m_window = createWindow("Bipolar", 1366, 768);
	m_window->setBackgroundColour(math::vec3(0.3f, 0.1f, 0.45f));

	// Create Shader
	graphics::Shader* shader = new graphics::Shader();
	shader->addSource(graphics::VERTEX_SHADER, "res/shaders/vertex.vert");
	shader->addSource(graphics::FRAGMENT_SHADER, "res/shaders/fragment.frag");
	shader->link();

	graphics::Shader* skyboxShader = new graphics::Shader();
	skyboxShader->addSource(graphics::VERTEX_SHADER, "res/shaders/skybox.vert");
	skyboxShader->addSource(graphics::FRAGMENT_SHADER, "res/shaders/skybox.frag");
	skyboxShader->link();

	graphics::Material* gold = new graphics::Material("res/materials/gold.mat");
	graphics::Material* rubber = new graphics::Material("res/materials/rubber.mat");

	graphics::Mesh* inner = new graphics::Mesh("res/models/mitsuba/mitsuba-sphere-inner.obj", "res/materials/rubber.mat");
	graphics::Mesh* outer = new graphics::Mesh("res/models/mitsuba/mitsuba-sphere-outer.obj", "res/materials/gold.mat");

	// Create Entity
	entity::Entity* entity = (new entity::Entity())
		->addComponent(new entity::TransformComponent(math::vec3(0.0f, 0.0f, 0.0f)))
		->addComponent(new entity::MeshComponent(inner));
	entity->getComponent<entity::MeshComponent>()->addMesh(outer);

	// Create Camera
	entity::Entity* camera = (new entity::Entity())
		->addComponent(new entity::TransformComponent(math::vec3(0.0f, 0.0f, 2.0f)))
		->addComponent(new entity::CameraComponent());

	// Create Light
	entity::Entity* light = (new entity::Entity())
		->addComponent(new entity::TransformComponent(math::vec3(-10.0f, 10.0f, 10.0f)))
		->addComponent(new entity::LightSourceComponent(math::vec3(0.9f), math::vec3(0.1f)));

	// Create Skybox
	graphics::CubeMap* skybox = new graphics::CubeMap(
		"res/images/skybox/right.jpg", "res/images/skybox/left.jpg",
		"res/images/skybox/top.jpg", "res/images/skybox/bottom.jpg",
		"res/images/skybox/back.jpg", "res/images/skybox/front.jpg"
	);

	// Create projection matrix
	math::mat4 projectionMatrix = math::mat4::perspective(60.0f, 1366.0f / 768.0f, 0.5f, 1000.0f);

	// Timing vars
	double previous = time::getTime();
	double lag = 0.0;
	double lastSecond = previous;
	long frames = 0;
	long updates = 0;

	MouseCaptureHandler captureHandler = MouseCaptureHandler();
	input::Keyboard::addKeyHandler(GLFW_KEY_ESCAPE, reinterpret_cast<input::KeyEventHandler*>(&captureHandler));

	// GAME LOOP ----------------------------------

	while (!shouldApplicationClose())
	{
		// Timing math
		double current = time::getTime();
		double delta = current - previous;
		previous = current;
		lag += delta;

		// Input
		getInput();

		camera->getComponent<entity::CameraComponent>()->update(delta);

		// Update
		while (lag >= time::MS_PER_UPDATE)
		{
			lag -= time::MS_PER_UPDATE;
			updates++;
		}

		// Rotate entity
//		entity->getComponent<entity::TransformComponent>()->rotation = math::vec3(sin(current) * 180, sin(current * 1.3f) * 180, sin(current * 0.8f) * 180);

		// Load uniforms
		shader->use();
		shader->loadUniform("model", entity->getComponent<entity::TransformComponent>()->getTransform());
		shader->loadUniform("view", camera->getComponent<entity::CameraComponent>()->getViewMatrix());
		shader->loadUniform("projection", projectionMatrix);
		shader->loadUniform("cameraPosition", camera->getComponent<entity::TransformComponent>()->position);
		light->getComponent<entity::LightSourceComponent>()->loadUniforms(shader);
		
		skyboxShader->use();
		skyboxShader->loadUniform("view", camera->getComponent<entity::CameraComponent>()->getViewMatrixNoTranslate());
		skyboxShader->loadUniform("projection", projectionMatrix);

		// Render
		m_window->beginRender();

		skyboxShader->use();
		skybox->render(skyboxShader);

		shader->use();
		skybox->bind();
		entity->getComponent<entity::MeshComponent>()->render(shader);

		m_window->swapBuffers();
		frames++;

		// Update FPS / UPS
		if (current - lastSecond >= 1)
		{
			m_window->setTitle("Bipolar :: FPS: " + std::to_string(frames) + " UPS: " + std::to_string(updates));
			lastSecond = current;
			frames = 0;
			updates = 0;
		}

		// Close windows
		processCloseRequests();
	}

	// CLEAN UP -----------------------------------

	delete gold;
	delete rubber;
	delete entity;
	delete camera;
	delete shader;
	delete skyboxShader;

	terminateEngine();

	return 0;
}

void MouseCaptureHandler::pressKey(GLuint key)
{
	bplr::input::Mouse::toggleCaptured(m_window);
}
