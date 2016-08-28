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

		struct Material
		{
			math::vec3 ambient;
			math::vec3 diffuse;
			math::vec3 specular;
			GLfloat shininess;
			bool useSpecMap = true;
		};

		class Mesh {
		public:
			Mesh(Shader* shader, std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures, Material material);
			Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures, Material material);
			Mesh(VAO* vao);
			~Mesh();

			void render(Shader* shader) const;

			void addTexture(Texture* texture);

		private:
			VAO* m_vao;
			std::vector<Texture*> m_textures;
			Material m_material;
		};
	}
}
