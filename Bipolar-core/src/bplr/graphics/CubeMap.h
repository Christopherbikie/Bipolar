#pragma once

#include "VAO.h"

namespace bplr
{
	namespace graphics
	{
		class CubeMap
		{
		public:
			CubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front);
			~CubeMap();

			void render(Shader* shader) const;

		private:
			GLuint m_location;
			VAO* m_vao;
		};
	}
}
