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
			void postLink() override;

			void drawRect() const;
		
		private:
			static GLboolean isGeometryInitialised;
			static VAO* rectangleVAO;
		};
	}
}
