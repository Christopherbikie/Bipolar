#include "FrameBufferTest.h"

FrameBufferTest::~FrameBufferTest()
{
	delete camera;
	delete scene;
	delete shader;
	delete skyboxShader;
	delete screenShader;
	delete rectVAO;
}

void FrameBufferTest::init(graphics::Window* window)
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

	screenShader = new graphics::Shader3D();
	screenShader->addSource(graphics::VERTEX_SHADER, "res/shaders/framebuffertest.vert");
	screenShader->addSource(graphics::FRAGMENT_SHADER, "res/shaders/framebuffertest.frag");
	screenShader->link();

	scene = new scene::Scene;

	// Create Camera
	camera = new scene::FPSCamera(math::vec3(0.0f, 0.0f, 2.0f), math::vec3(0.0f), 60.0f, 1366.0f / 768.0f);

	// Create Player
	player = std::shared_ptr<scene::Entity>((new scene::Entity())
		->addComponent(new scene::TransformComponent(math::vec3(0.0f, 0.0f, 2.0f)))
		->addComponent(new scene::CameraComponent(camera)));
	scene->setCamera(player.get());

	// Create Entities
	std::shared_ptr<scene::Entity> plane((new scene::Entity())
		->addComponent(new scene::TransformComponent(math::vec3(-1.0f, 0.0f, 0.0f), 1.5f))
		->addComponent(new scene::MeshComponent(assets::ModelLoader::loadModel("res/models/util/plane.obj"))));
	scene->addEntity(plane);
	std::shared_ptr<scene::Entity> entity((new scene::Entity())
		->addComponent(new scene::TransformComponent(math::vec3(1.0f, 0.0f, 0.0f)))
		->addComponent(new scene::MeshComponent(assets::ModelLoader::loadModel("res/models/mitsuba/mitsuba-sphere.obj"))));
	scene->addEntity(entity);

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

	FrameBufferTestInputHandler* inputHandler = new FrameBufferTestInputHandler(this);
	input::Keyboard::addKeyHandler(GLFW_KEY_ESCAPE, inputHandler);
	input::Keyboard::addKeyHandler(GLFW_KEY_R, inputHandler);

	framebuffer = new graphics::Framebuffer;

	GLfloat quadVertices[] = {
		-1.0f,  1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f,

		-1.0f,  1.0f,
		1.0f, -1.0f,
		1.0f,  1.0f
	};

	GLfloat quadTextureCoords[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	rectVAO = new graphics::VAO;
	rectVAO->bind();
	rectVAO->storeInBuffer(0, 2, 6, quadVertices);
	rectVAO->storeInBuffer(2, 2, 6, quadTextureCoords);
	rectVAO->unbind();
}

void FrameBufferTest::update(float delta)
{
	player->getComponent<scene::CameraComponent>()->update(delta);
}

void FrameBufferTest::render()
{
	//Draw scene to framebuffer
	framebuffer->bind();
	framebuffer->clear();

	skyboxShader->use();
	skyboxShader->loadUniform("view", camera->getViewMatrixNoTranslate());
	skyboxShader->loadUniform("projection", camera->getProjectionMatrix());

	skyboxShader->use();
	skybox->render(skyboxShader);

	scene->render(shader);
	scene->post();

	// Draw Screen
	framebuffer->bindDefault();

	screenShader->use();
	rectVAO->bind();
	framebuffer->bindTexture(screenShader, "screenTexture");
	screenShader->drawArrays(0, rectVAO->getVertexCount());
	rectVAO->unbind();
}

FrameBufferTestInputHandler::FrameBufferTestInputHandler(FrameBufferTest* layer)
{
	m_layer = layer;
}

void FrameBufferTestInputHandler::pressKey(GLuint key)
{
	if (key == GLFW_KEY_ESCAPE)
		input::Mouse::toggleCaptured(m_layer->getWindow());
}
