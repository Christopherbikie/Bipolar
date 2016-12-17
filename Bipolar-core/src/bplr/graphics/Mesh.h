#pragma once

#include "../math/vec2.h"
#include "../math/vec3.h"
#include <vector>
#include "Shader3D.h"
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
			Mesh(std::string objPath, Material* material = new Material());
			Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, Material* material);
			~Mesh();

			void render(Shader3D* shader) const;

		private:
			VAO* m_vao;
			std::vector<Texture*> m_textures;
			Material* m_material;
		};
	}
}
