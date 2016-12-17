#pragma once

#include <vector>
#include "Mesh.h"

namespace bplr
{
	namespace graphics
	{
		class Model
		{
		public:
			Model();
			Model(std::string path);
			Model(Mesh* mesh);
			Model(std::vector<Mesh*> meshes);

			void addMesh(Mesh* mesh);
			void addMeshes(std::vector<Mesh*> meshes);
			std::vector<Mesh*> getMeshes() const;

			std::string getPath() const;

			void render(Shader3D* shader) const;

		private:
			std::vector<Mesh*> m_meshes;
			std::string path;
		};

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
