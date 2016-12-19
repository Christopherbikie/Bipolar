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

		ModelStore::ModelStore()
		{
		}

		ModelStore::~ModelStore()
		{
			for (std::pair<std::string, Model*> model : m_models)
				delete model.second;
		}

		void ModelStore::add(Model* model)
		{
			m_models[model->getPath()] = model;
		}

		Model* ModelStore::get(std::string path)
		{
			if (m_models.find(path) == m_models.end())
				return nullptr;
			return m_models[path];
		}

		void ModelStore::clear()
		{
			for (std::pair<std::string, Model*> model : m_models)
				delete model.second;
			m_models.clear();
		}

		std::vector<std::string> ModelStore::getModelPaths()
		{
			std::vector<std::string> paths;
			for (std::pair<std::string, Model*> model : m_models)
				paths.push_back(model.first);
			return paths;
		}
	}
}
