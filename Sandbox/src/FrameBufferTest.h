#pragma once

#include <Bipolar.h>

using namespace bplr;

const std::string vertShaderPath = "res/shaders/vertex.vert";
const std::string fragShaderPath = "res/shaders/fragment.frag";
const std::string skyboxVertShaderPath = "res/shaders/skybox.vert";
const std::string skyboxFragShaderPath = "res/shaders/skybox.frag";

class FrameBufferTest : public graphics::Layer
{
public:
	~FrameBufferTest();

	void init(graphics::Window* window) override;
	void update(float delta) override;
	void render() override;

private:
	graphics::Shader3D* shader;
	graphics::Shader3D* skyboxShader;
	graphics::Shader3D* screenShader;

	scene::FPSCamera* camera;

	scene::Entity* player;
	scene::Entity* entity1;
	scene::Entity* entity2;
	scene::Entity* light;

	graphics::CubeMap* skybox;

	graphics::Framebuffer* framebuffer;
	graphics::VAO* rectVAO;
};

class FrameBufferTestInputHandler : public input::KeyEventHandler
{
public:
	FrameBufferTestInputHandler(FrameBufferTest* Layer);
	void pressKey(GLuint key) override;

private:
	FrameBufferTest* m_layer;
};