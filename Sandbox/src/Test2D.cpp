#include "Test2D.h"

GLchar* vertShaderPath = "res/shaders/test2d.vert";
GLchar* fragShaderPath = "res/shaders/test2d.frag";

Test2D::~Test2D()
{
	delete shader;
}

void Test2D::init(graphics::Window* window)
{
	m_window = window;

	// Create Shader
	shader = new graphics::Shader2D();
	shader->addSource(graphics::VERTEX_SHADER, vertShaderPath);
	shader->addSource(graphics::FRAGMENT_SHADER, fragShaderPath);
	shader->link();
}

void Test2D::render()
{
	shader->drawRect();
}
