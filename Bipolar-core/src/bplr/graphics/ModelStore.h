#pragma once

#include <string>
#include <vector>
#include <map>

namespace bplr
{
	namespace graphics
	{
		class Model;

		class ModelStore
		{
		public:
			ModelStore();
			~ModelStore();

			void add(Model* model);
			Model* get(std::string path);

			void clear();

			std::vector<std::string> getModelPaths();

		private:
			std::map<std::string, Model*> m_models;
		};

		static ModelStore* modelStore = new ModelStore;
	}
}
