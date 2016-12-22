#include "Test3D.h"

Test3D::~Test3D()
{
	delete camera;
	delete scene;
	delete shader;
	delete skyboxShader;
}

void Test3D::init(graphics::Window* window)
{
	m_window = window;

	// Create Shader
	shader = new graphics::Shader3D();
	shader->addSource(graphics::VERTEX_SHADER, vertShaderPath.c_str());
	shader->addSource(graphics::FRAGMENT_SHADER, fragShaderPath.c_str());
	shader->link();

	skyboxShader = new graphics::Shader3D();
	skyboxShader->addSource(graphics::VERTEX_SHADER, skyboxVertShaderPath.c_str());
	skyboxShader->addSource(graphics::FRAGMENT_SHADER, skyboxFragShaderPath.c_str());
	skyboxShader->link();

	scene = new scene::Scene;

	// Create Camera
	camera = new scene::FPSCamera(math::vec3(0.0f, 0.0f, 2.0f), math::vec3(0.0f), 60.0f, 1366.0f / 768.0f);

	// Create Player
	std::shared_ptr<scene::Entity> player((new scene::Entity())
		->addComponent(new scene::TransformComponent(math::vec3(0.0f, 0.0f, 2.0f)))
		->addComponent(new scene::CameraComponent(camera)));
	scene->addEntity(player);
	scene->setCamera(player.get());

	// Create Entities
	std::shared_ptr<scene::Entity> plane((new scene::Entity())
		->addComponent(new scene::TransformComponent(math::vec3(0.0f, 0.0f, -4.5f), 1.5f))
		->addComponent(new scene::MeshComponent(assets::ModelLoader::loadModel("res/models/util/plane.obj"))));
	scene->addEntity(plane);

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			std::shared_ptr<scene::Entity> entity((new scene::Entity())
				->addComponent(new scene::TransformComponent(math::vec3(-4.5f + i * 3, 0.0f, j * -3)))
				->addComponent(new scene::MeshComponent(assets::ModelLoader::loadModel("res/models/mitsuba/mitsuba-sphere.obj"))));
			entity->getComponent<scene::MeshComponent>()->getMesh(1)->getMaterial()->setAlbedo(math::vec3(1.0f, 0.2f, 0.2f));
			scene->addEntity(entity);
		}

	// Create Light
	std::shared_ptr<scene::Entity> light((new scene::Entity())
		->addComponent(new scene::TransformComponent(math::vec3(-10.0f, 10.0f, 10.0f)))
		->addComponent(new scene::LightSourceComponent(math::vec3(0.9f), math::vec3(0.1f))));
	scene->addLight(light);

	// Create Skybox
	skybox = new graphics::CubeMap(
		"res/images/skybox/right.jpg", "res/images/skybox/left.jpg",
		"res/images/skybox/top.jpg", "res/images/skybox/bottom.jpg",
		"res/images/skybox/back.jpg", "res/images/skybox/front.jpg"
	);
	scene->setEnvMap(skybox);

	InputHandler* inputHandler = new InputHandler(this);
	input::Keyboard::addKeyHandler(GLFW_KEY_ESCAPE, inputHandler);
	input::Keyboard::addKeyHandler(GLFW_KEY_R, inputHandler);
}

void Test3D::update(float delta)
{
	scene->update(delta);
}

void Test3D::render()
{
	skyboxShader->use();
	skyboxShader->loadUniform("view", camera->getViewMatrixNoTranslate());
	skyboxShader->loadUniform("projection", camera->getProjectionMatrix());

	skyboxShader->use();
	skybox->render(skyboxShader);

	scene->render(shader);
	scene->post();
}

InputHandler::InputHandler(Test3D* layer)
{
	m_layer = layer;
}

void InputHandler::pressKey(GLuint key)
{
	if (key == GLFW_KEY_ESCAPE)
		input::Mouse::toggleCaptured(m_layer->getWindow());
}
