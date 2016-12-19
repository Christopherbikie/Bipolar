#include "ModelStore.h"
#include "Model.h"

namespace bplr
{
	namespace graphics
	{
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
