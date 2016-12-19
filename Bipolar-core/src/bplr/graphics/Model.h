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
			// Only works if path has not been set!
			void setPath(std::string path);

			void render(Shader3D* shader) const;

		private:
			std::vector<Mesh*> m_meshes;
			std::string m_path;
		};
	}
}
