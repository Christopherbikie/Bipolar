#include "Model.h"
#include <iostream>

namespace bplr
{
	namespace graphics
	{
		Model::Model()
		{
		}

		Model::Model(std::string path)
		{
		}

		Model::Model(Mesh* mesh)
		{
			m_meshes.push_back(mesh);
		}

		Model::Model(std::vector<Mesh*> meshes)
		{
			m_meshes = meshes;
		}

		void Model::addMesh(Mesh* mesh)
		{
			m_meshes.push_back(mesh);
		}

		void Model::addMeshes(std::vector<Mesh*> meshes)
		{
			m_meshes.insert(m_meshes.end(), meshes.begin(), meshes.end());
		}

		std::vector<Mesh*> Model::getMeshes() const
		{
			return m_meshes;
		}

		std::string Model::getPath() const
		{
			return m_path;
		}

		void Model::setPath(std::string path)
		{
			if (m_path.empty())
				m_path = path;
			else
				std::cout << "Attemped to write path to model when path was already assigned!" << std::endl
				<< "Current: " << m_path << std::endl
				<< "Attemped change: " << path << std::endl;
		}

		void Model::render(Shader3D* shader) const
		{
			for (Mesh* mesh : m_meshes)
				mesh->render(shader);
		}
	}
}
