#pragma once

#include "../math/vec2.h"
#include "../math/vec3.h"
#include <vector>
#include "Texture.h"
#include "VAO.h"
#include "Material.h"

namespace bplr
{
	namespace graphics
	{
		struct Vertex {
			math::vec3 position;
			math::vec3 normal;
			math::vec2 textureCoord;
		};

		class Mesh {
		public:
			Mesh(std::string objPath, std::string matPath);
			Mesh(std::string objPath, Material* material = new Material());
			~Mesh();

			void render(Shader* shader) const;

		private:
			VAO* m_vao;
			Material* m_material;
		};
	}
}
