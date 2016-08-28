#pragma once

#include "Component.h"
#include "../../graphics/Mesh.h"
#include "scene.h"

namespace bplr
{
	namespace entity
	{
		class MeshComponent : public Component
		{
		public:
			MeshComponent(graphics::Mesh* mesh);
			MeshComponent(std::string modelPath);
			~MeshComponent();

			void addMesh(graphics::Mesh* mesh);
			void addTexture(std::string path, int meshIndex = 0);

			void render(graphics::Shader* shader) const;

			std::string getType() override;
			static std::string getStaticType();
			
		private:
			std::vector<graphics::Mesh*> m_meshes;
			std::vector<graphics::Texture*> m_textures;
			std::string m_directory;

			void processNode(aiNode* node, const aiScene* scene);
			graphics::Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
			std::vector<graphics::Texture*> loadMaterialTextures(aiMaterial* material, aiTextureType type, graphics::TextureType bplrType, graphics::Material* myMaterial);
		};
	}
}
