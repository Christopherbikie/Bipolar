#pragma once

#include "Bipolar.h"

bplr::graphics::Window* m_window;

bplr::graphics::Shader* shader;
bplr::graphics::Shader* skyboxShader;

const std::string vertShaderPath = "res/shaders/vertex.vert";
const std::string fragShaderPath = "res/shaders/fragment.frag";
const std::string skyboxVertShaderPath = "res/shaders/skybox.vert";
const std::string skyboxFragShaderPath = "res/shaders/skybox.frag";

int main();
void reloadShaders();

class InputHandler : bplr::input::KeyEventHandler
{
public:
	void pressKey(GLuint key) override;
};
