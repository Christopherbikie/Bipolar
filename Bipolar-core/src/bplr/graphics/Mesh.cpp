#include "Mesh.h"
#include <sstream>

namespace bplr
{
	namespace graphics
	{
		Mesh::Mesh(Shader* shader, std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures)
			: m_vao(new VAO), m_textures(textures)
		{
			std::vector<math::vec3> positions;
			std::vector<math::vec3> normals;
			std::vector<math::vec2> textureCoords;

			for (Vertex vertex : vertices)
			{
				positions.push_back(vertex.position);
				normals.push_back(vertex.normal);
				textureCoords.push_back(vertex.textureCoord);
			}

			m_vao->bind();
			m_vao->storeInBuffer(shader, "position", 3, positions.size(), (GLfloat*) &positions[0]);
			m_vao->storeInBuffer(shader, "textureCoords", 2, textureCoords.size(), (GLfloat*) &textureCoords[0]);
			m_vao->storeInBuffer(shader, "normal", 3, normals.size(), (GLfloat*) &normals[0]);
			m_vao->storeInElementBuffer(indices.size(), &indices[0]);
			m_vao->unbind();
		}

		Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture*> textures)
			: m_vao(new VAO), m_textures(textures)
		{
			std::vector<math::vec3> positions;
			std::vector<math::vec3> normals;
			std::vector<math::vec2> textureCoords;

			for (Vertex vertex : vertices)
			{
				positions.push_back(vertex.position);
				normals.push_back(vertex.normal);
				textureCoords.push_back(vertex.textureCoord);
			}

			m_vao->bind();
			m_vao->storeInBuffer(0, 3, positions.size(), (GLfloat*) &positions[0]);
			m_vao->storeInBuffer(1, 2, textureCoords.size(), (GLfloat*)&textureCoords[0]);
			m_vao->storeInBuffer(2, 3, normals.size(), (GLfloat*) &normals[0]);
			m_vao->storeInElementBuffer(indices.size(), &indices[0]);
			m_vao->unbind();
		}

		Mesh::Mesh(VAO* vao)
			: m_vao(vao)
		{
		}

		Mesh::~Mesh()
		{
			delete m_vao;
		}

		void Mesh::render(Shader* shader) const
		{
			std::map<TextureType, GLuint> numberOfTypes;
			for (GLint i = 0; i < m_textures.size(); ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i);

				std::stringstream ss;

				switch (m_textures[i]->getType())
				{
				case DiffuseMap:
					ss << typeNames[DiffuseMap] << numberOfTypes[DiffuseMap]++;
					break;
				case SpecularMap:
					ss << typeNames[SpecularMap] << numberOfTypes[SpecularMap]++;
					break;
				default:
					break;
				}

				m_textures[i]->bind(shader, ss.str().c_str());
			}
			glActiveTexture(GL_TEXTURE0);

			shader->use();
			m_vao->bind();
			m_vao->bindEBO();
			shader->drawElements(m_vao->getVertexCount());
			m_vao->unbind();
		}
	}
}
