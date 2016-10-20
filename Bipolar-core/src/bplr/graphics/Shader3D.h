#pragma once

#include "Shader.h"

namespace bplr
{
	namespace graphics
	{
		class Shader3D : public Shader
		{
		public:
			void drawArrays(GLint first, GLint count) const;
			void drawElements(GLint count);
		};
	}
}
