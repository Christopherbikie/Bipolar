#include "Test3D.h"

Test3D::~Test3D()
{
	delete entity1;
	delete entity2;
	delete camera;
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


	// Create Camera
	camera = new graphics::FPSCamera(math::vec3(0.0f, 0.0f, 2.0f), math::vec3(0.0f), 60.0f, 1366.0f / 768.0f);

	// Create Player
	player = (new entity::Entity())
		->addComponent(new entity::TransformComponent(math::vec3(0.0f, 0.0f, 2.0f)))
		->addComponent(new entity::CameraComponent(camera));

	// Create Entity
	graphics::Model* model1 = assets::ModelLoader::loadModel("res/models/earth/earth.obj");
	entity1 = (new entity::Entity())
		->addComponent(new entity::TransformComponent(math::vec3(-1.0f, 0.0f, 0.0f)))
		->addComponent(new entity::MeshComponent(model1));
	graphics::Model* model2 = assets::ModelLoader::loadModel("res/models/earth/earth.obj");
	entity2 = (new entity::Entity())
		->addComponent(new entity::TransformComponent(math::vec3(1.0f, 0.0f, 0.0f)))
		->addComponent(new entity::MeshComponent(model2));

	// Create Light
	light = (new entity::Entity())
		->addComponent(new entity::TransformComponent(math::vec3(-10.0f, 10.0f, 10.0f)))
		->addComponent(new entity::LightSourceComponent(math::vec3(0.9f), math::vec3(0.1f)));

	// Create Skybox
	skybox = new graphics::CubeMap(
		"res/images/skybox/right.jpg", "res/images/skybox/left.jpg",
		"res/images/skybox/top.jpg", "res/images/skybox/bottom.jpg",
		"res/images/skybox/back.jpg", "res/images/skybox/front.jpg"
	);

	InputHandler* inputHandler = new InputHandler(this);
	input::Keyboard::addKeyHandler(GLFW_KEY_ESCAPE, inputHandler);
	input::Keyboard::addKeyHandler(GLFW_KEY_R, inputHandler);
}

void Test3D::update(float delta)
{
	player->getComponent<entity::CameraComponent>()->update(delta);
}

void Test3D::render()
{
	skyboxShader->use();
	skyboxShader->loadUniform("view", camera->getViewMatrixNoTranslate());
	skyboxShader->loadUniform("projection", camera->getProjectionMatrix());

	skyboxShader->use();
	skybox->render(skyboxShader);

	shader->use();
	shader->loadUniform("view", camera->getViewMatrix());
	shader->loadUniform("projection", camera->getProjectionMatrix());
	shader->loadUniform("cameraPosition", camera->getPosition());
	light->getComponent<entity::LightSourceComponent>()->loadUniforms(shader);
	skybox->bind();

	shader->loadUniform("model", entity1->getComponent<entity::TransformComponent>()->getTransform());
	entity1->getComponent<entity::MeshComponent>()->render(shader);
	shader->loadUniform("model", entity2->getComponent<entity::TransformComponent>()->getTransform());
	entity2->getComponent<entity::MeshComponent>()->render(shader);
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
