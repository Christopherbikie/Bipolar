#define TINYOBJLOADER_IMPLEMENTATION

#include "Mesh.h"
#include <tiny_obj_loader.h>
#include <iostream>

namespace bplr
{
	namespace graphics
	{
		Mesh::Mesh(std::string objPath, std::string matPath)
			: Mesh(objPath, new Material(matPath))
		{
		}

		Mesh::Mesh(std::string objPath, Material* material)
			: m_vao(new VAO()), m_material(material)
		{
			std::vector<std::vector<math::vec3>>vertices;
			std::vector<std::vector<math::vec3>>normals;
			std::vector<std::vector<math::vec2>>texcoords;
			std::vector<std::vector<GLuint>>indices;
			std::vector<std::string>names;

			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;
			std::stringstream ifs;
			ifs << objPath;

			std::string err;
			tinyobj::LoadObj(shapes, materials, err, objPath.c_str());

			std::cout << " # of shapes : " << shapes.size() << std::endl;

			vertices.resize(shapes.size());
			normals.resize(shapes.size());
			texcoords.resize(shapes.size());
			indices.resize(shapes.size());
			names.resize(shapes.size());

			// convert between mesh loader data structure and vector data structure
			for (size_t i = 0; i < shapes.size(); i++) {
				vertices[i].resize(shapes[i].mesh.positions.size() / 3);
				normals[i].resize(shapes[i].mesh.normals.size() / 3);
				texcoords[i].resize(shapes[i].mesh.texcoords.size() / 2);
				indices[i].resize(shapes[i].mesh.indices.size());
				names[i] = shapes[i].name;

				std::cout << shapes[i].mesh.positions.size() / 3 << " " << shapes[i].mesh.normals.size() / 3 << " "
					<< shapes[i].mesh.texcoords.size() / 2 << " " << shapes[i].mesh.indices.size() << std::endl;

				for (size_t v = 0; v < shapes[i].mesh.positions.size() / 3; v++) {
					vertices[i][v] = math::vec3(shapes[i].mesh.positions[3 * v + 0], shapes[i].mesh.positions[3 * v + 1],
						shapes[i].mesh.positions[3 * v + 2]);
				}
				for (size_t n = 0; n < shapes[i].mesh.normals.size() / 3; n++) {
					normals[i][n] = math::vec3(shapes[i].mesh.normals[3 * n + 0], shapes[i].mesh.normals[3 * n + 1],
						shapes[i].mesh.normals[3 * n + 2]);
				}
				for (size_t t = 0; t < shapes[i].mesh.texcoords.size() / 2; t++) {
					texcoords[i][t] = math::vec2(shapes[i].mesh.texcoords[2 * t + 0], shapes[i].mesh.texcoords[2 * t + 1] * -1);
				}
				for (size_t f = 0; f < shapes[i].mesh.indices.size(); f++) {
					indices[i][f] = shapes[i].mesh.indices[f];
				}
			}

			m_vao->bind();
			m_vao->storeInBuffer(0, 3, vertices[0].size(), (GLfloat*)&vertices[0][0]);
			m_vao->storeInBuffer(1, 3, normals[0].size(), (GLfloat*)&normals[0][0]);
			m_vao->storeInBuffer(2, 2, texcoords[0].size(), (GLfloat*)&texcoords[0][0]);
			m_vao->storeInElementBuffer(indices[0].size(), &indices[0][0]);
			m_vao->unbind();
		}

		Mesh::~Mesh()
		{
			delete m_vao;
			delete m_material;
		}

		void Mesh::render(Shader3D* shader) const
		{
			m_material->loadUniforms(shader);

			shader->use();
			m_vao->bind();
			m_vao->bindEBO();
			shader->drawElements(m_vao->getVertexCount());
			m_vao->unbind();
		}
	}
}
