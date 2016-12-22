#pragma once

#include <Bipolar.h>

using namespace bplr;

const std::string vertShaderPath = "res/shaders/geometryPass.vert";
const std::string fragShaderPath = "res/shaders/geometryPass.frag";
const std::string skyboxVertShaderPath = "res/shaders/skybox.vert";
const std::string skyboxFragShaderPath = "res/shaders/skybox.frag";

class DeferredTest : public graphics::Layer
{
public:
	~DeferredTest();

	void init(graphics::Window* window) override;
	void update(float delta) override;
	void render() override;

private:
	graphics::Shader3D* shader;
	graphics::Shader3D* skyboxShader;
	graphics::Shader3D* screenShader;
	graphics::CubeMap* skybox;

	scene::FPSCamera* camera;
	scene::Scene* scene;

	graphics::GBuffer* gBuffer;
};

class FrameBufferTestInputHandler : public input::KeyEventHandler
{
public:
	FrameBufferTestInputHandler(DeferredTest* Layer);
	void pressKey(GLuint key) override;

private:
	DeferredTest* m_layer;
};
