#pragma once

#include <Bipolar.h>

using namespace bplr;

class Test2D : public graphics::Layer
{
public:
	~Test2D();

	void init(graphics::Window* window) override;
	void render() override;

private:
	graphics::Shader2D* shader;
};
