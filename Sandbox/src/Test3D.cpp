#include "Test3D.h"

Test3D::~Test3D()
{
	delete entity;
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

	graphics::Material* gold = new graphics::Material("res/materials/gold.mat");
	graphics::Material* rubber = new graphics::Material("res/materials/rubber.mat");

	graphics::Mesh* inner = new graphics::Mesh("res/models/mitsuba/mitsuba-sphere-inner.obj", "res/materials/rubber.mat");
	graphics::Mesh* outer = new graphics::Mesh("res/models/mitsuba/mitsuba-sphere-outer.obj", "res/materials/gold.mat");

	// Create Camera
	camera = new graphics::FPSCamera(math::vec3(0.0f, 0.0f, 2.0f), math::vec3(0.0f), 60.0f, 1366.0f / 768.0f);

	// Create Entity
	entity = (new entity::Entity())
		->addComponent(new entity::TransformComponent(math::vec3(0.0f, 0.0f, 0.0f)))
		->addComponent(new entity::MeshComponent(inner));
	    entity->getComponent<entity::MeshComponent>()->addMesh(outer);

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
}

void Test3D::render()
{
	// Load uniforms
	shader->use();
	shader->loadUniform("model", entity->getComponent<entity::TransformComponent>()->getTransform());
	shader->loadUniform("view", camera->getViewMatrix());
	shader->loadUniform("projection", camera->getProjectionMatrix());
	shader->loadUniform("cameraPosition", camera->getPosition());
	light->getComponent<entity::LightSourceComponent>()->loadUniforms(shader);

	skyboxShader->use();
	skyboxShader->loadUniform("view", camera->getViewMatrixNoTranslate());
	skyboxShader->loadUniform("projection", camera->getProjectionMatrix());

	skyboxShader->use();
	skybox->render(skyboxShader);

	shader->use();
	skybox->bind();
	entity->getComponent<entity::MeshComponent>()->render(shader);
}

InputHandler::InputHandler(Test3D* layer)
{
	m_layer = layer;
}

void InputHandler::pressKey(GLuint key)
{
	if (key == GLFW_KEY_ESCAPE)
		bplr::input::Mouse::toggleCaptured(m_layer->getWindow());
}
