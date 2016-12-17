#pragma once

#include <scene.h>
#include "../graphics/Model.h"

namespace bplr
{
	namespace assets
	{
		extern const std::vector<std::string> assimpFiles;

		class ModelLoader
		{
		public:
			static graphics::Model* loadModel(std::string path);

		private:
			static graphics::Model* assimpLoadModel(std::string path);
			static std::vector<graphics::Mesh*> assimpProcessNode(aiNode* node, const aiScene* scene, std::string path);
			static graphics::Mesh* assimpProcessMesh(aiMesh* mesh, const aiScene* scene, std::string path);
			static void assimpLoadMaterialTextures(aiMaterial* material, aiTextureType type, graphics::TextureType bplrType, graphics::Material* myMaterial, std::string path);
		};
	}
}
