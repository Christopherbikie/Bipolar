#pragma once

#include <Bipolar.h>

using namespace bplr;

const std::string vertShaderPath = "res/shaders/vertex.vert";
const std::string fragShaderPath = "res/shaders/fragment.frag";
const std::string skyboxVertShaderPath = "res/shaders/skybox.vert";
const std::string skyboxFragShaderPath = "res/shaders/skybox.frag";

class Test3D : public graphics::Layer
{
public:
	~Test3D();

	void init(graphics::Window* window) override;
	void update(float delta) override;
	void render() override;

	void reloadShaders() const;

private:
	graphics::Shader* shader;
	graphics::Shader* skyboxShader;

	entity::Entity* entity;
	entity::Entity* camera;
	entity::Entity* light;

	graphics::CubeMap* skybox;

	math::mat4 projectionMatrix;
};

class InputHandler : public input::KeyEventHandler
{
public:
	InputHandler(Test3D* Layer);
	void pressKey(GLuint key) override;
	
private:
	Test3D* m_layer;
};

