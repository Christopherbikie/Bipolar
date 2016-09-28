#include "MeshComponent.h"
#include <iostream>
#include <postprocess.h>
#include <Importer.hpp>

namespace bplr
{
	namespace entity
	{
		MeshComponent::MeshComponent(graphics::Mesh* mesh)
		{
			m_meshes.push_back(mesh);
		}

		MeshComponent::MeshComponent(std::string modelPath)
		{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate);

			if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "Failed to load model at " << modelPath << std::endl
					<< importer.GetErrorString() << std::endl;
				return;
			}

			m_directory = modelPath.substr(0, modelPath.find_last_of('/'));
			processNode(scene->mRootNode, scene);

			importer.FreeScene();
		}

		MeshComponent::~MeshComponent()
		{
			for (graphics::Mesh* mesh : m_meshes)
				delete mesh;
			for (graphics::Texture* texture : m_textures)
				delete texture;
		}

		void MeshComponent::addMesh(graphics::Mesh* mesh)
		{
			m_meshes.push_back(mesh);
		}

		void MeshComponent::addTexture(std::string path, int meshIndex)
		{
			graphics::Texture* texture = new graphics::Texture(path.c_str());
			m_meshes[meshIndex]->addTexture(texture);
			m_textures.push_back(texture);
		}

		void MeshComponent::render(graphics::Shader *shader) const
		{
			for (graphics::Mesh* mesh : m_meshes)
				mesh->render(shader);
		}

		std::string MeshComponent::getType()
		{
			return getStaticType();
		}

		std::string MeshComponent::getStaticType()
		{
			return "Mesh";
		}

		void MeshComponent::processNode(aiNode* node, const aiScene* scene)
		{
			for (GLuint i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				m_meshes.push_back(processMesh(mesh, scene));
			}

			for (GLuint i = 0; i < node->mNumChildren; i++)
				processNode(node->mChildren[i], scene);
		}

		graphics::Mesh* MeshComponent::processMesh(aiMesh* mesh, const aiScene* scene)
		{
			std::vector<graphics::Vertex> vertices;
			std::vector<GLuint> indices;
			std::vector<graphics::Texture*> textures;

			for (int i = 0; i < mesh->mNumVertices; ++i)
			{
				graphics::Vertex vertex;

				vertex.position.x = mesh->mVertices[i].x;
				vertex.position.y = mesh->mVertices[i].y;
				vertex.position.z = mesh->mVertices[i].z;

				vertex.normal.x = mesh->mNormals[i].x;
				vertex.normal.y = mesh->mNormals[i].y;
				vertex.normal.z = mesh->mNormals[i].z;

				if (mesh->mTextureCoords[0])
				{
					vertex.textureCoord.x = mesh->mTextureCoords[0][i].x;
					vertex.textureCoord.y = mesh->mTextureCoords[0][i].y;
				}
				else
					vertex.textureCoord = math::vec2(0.0f);

				vertices.push_back(vertex);
			}

			for (int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (int j = 0; j < face.mNumIndices; j++)
					indices.push_back((face.mIndices[j]));
			}

			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			graphics::MaterialStruct myMaterial;

			if (mesh->mMaterialIndex >= 0)
			{
				std::map<graphics::TextureType, std::vector<graphics::Texture*>> textureMaps;

				textureMaps[graphics::AlbedoMap] = loadMaterialTextures(material, aiTextureType_DIFFUSE, graphics::AlbedoMap, &myMaterial);
				textures.insert(textures.end(), textureMaps[graphics::AlbedoMap].begin(), textureMaps[graphics::AlbedoMap].end());

				textureMaps[graphics::SpecularMap] = loadMaterialTextures(material, aiTextureType_SPECULAR, graphics::SpecularMap, &myMaterial);
				textures.insert(textures.end(), textureMaps[graphics::SpecularMap].begin(), textureMaps[graphics::SpecularMap].end());
			}

			aiColor3D ambient;
			material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
			myMaterial.ambient = math::vec3(ambient.r, ambient.g, ambient.b);

			aiColor3D diffuse;
			material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			myMaterial.albedo = math::vec3(diffuse.r, diffuse.g, diffuse.b);

			aiColor3D specular;
			material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
			myMaterial.specular = math::vec3(specular.r, specular.g, specular.b);

			GLfloat shininess;
			material->Get(AI_MATKEY_SHININESS, shininess);
			myMaterial.shininess = shininess;

			return new graphics::Mesh(vertices, indices, textures, myMaterial);
		}

		std::vector<graphics::Texture*> MeshComponent::loadMaterialTextures(aiMaterial* material, aiTextureType type, graphics::TextureType bplrType, graphics::MaterialStruct* myMaterial)
		{
			std::vector<graphics::Texture*> textures;
			if (material->GetTextureCount(type) > 0)
				for (int i = 0; i < material->GetTextureCount(type); i++)
				{
					aiString string;
					material->GetTexture(type, i, &string);
					GLboolean skip = false;

					for (int j = 0; j < m_textures.size(); ++j)
					{
						if (m_textures[j]->getPath() == string)
						{
							textures.push_back(m_textures[j]);
							skip = true;
							break;
						}
					}
					if (!skip)
					{
						graphics::Texture* texture = new graphics::Texture((m_directory + "/" + string.C_Str()).c_str(), bplrType);
						textures.push_back(texture);
						m_textures.push_back(texture);
					}
				}
			else
			{
				graphics::Texture* texture = new graphics::Texture("res/images/white.png", bplrType);
				m_textures.push_back(texture);
				textures.push_back(texture);
				if (bplrType == graphics::SpecularMap)
					myMaterial->useSpecMap = false;
			}
			return textures;
		}
	}
}
