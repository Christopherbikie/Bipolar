#pragma once

#include "Shader.h"
#include "VAO.h"

namespace bplr
{
	namespace graphics
	{
		class Shader2D : public Shader
		{
		public:
			void drawRect() const;
		};
	}
}
