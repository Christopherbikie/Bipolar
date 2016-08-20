#pragma once

#include "../math/vec2.h"
#include "../math/vec3.h"
#include <vector>
#include "Texture.h"
#include "VAO.h"

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
			Mesh(Shader* shader, std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures);
			Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures);
			Mesh(VAO* vao);
			~Mesh();

			void render(Shader* shader) const;

		private:
			VAO* m_vao;
			std::vector<Texture*> m_textures;
		};
	}
}
