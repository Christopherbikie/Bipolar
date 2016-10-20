#pragma once

#include "Shader.h"

namespace bplr
{
	namespace graphics
	{
		class Shader2D : public Shader
		{
		public:
			void drawPoint(math::vec2 position, math::vec3 colour = math::vec3(1.0f), GLfloat radius);
		};
	}
}
