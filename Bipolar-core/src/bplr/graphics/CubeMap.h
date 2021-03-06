#pragma once

#include "VAO.h"
#include "Shader3D.h"

namespace bplr
{
	namespace graphics
	{
		class CubeMap
		{
		public:
			CubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front);
			~CubeMap();

			void render(Shader3D* shader) const;
			void bind() const;

		private:
			GLuint m_location;
			VAO* m_vao;
		};
	}
}
