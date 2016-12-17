#include "ModelLoader.h"
#include <iostream>
#include <postprocess.h>
#include <Importer.hpp>

namespace bplr
{
	namespace assets
	{
		const std::vector<std::string> assimpFiles = {
			"obj",
			"mtl",
			"ply",
			"blend",
			"dae",
			"stl",
		};

		graphics::Model* ModelLoader::loadModel(std::string path)
		{
			graphics::Model* previousModel = graphics::modelStore->get(path);

			if (previousModel != nullptr)
				return previousModel;

			std::string fileExtention = path.substr(path.find_last_of(".") + 1);
			if (fileExtention == path)
			{
				std::cout << "Attempted to load a model with no file extention" << std::endl
					<< "Path: " << path << std::endl;
				return new graphics::Model;
			}

			if (find(assimpFiles.begin(), assimpFiles.end(), fileExtention) != assimpFiles.end())
				return assimpLoadModel(path);

			return new graphics::Model;
		}

		graphics::Model* ModelLoader::assimpLoadModel(std::string path)
		{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

			if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << "Failed to load model at " << path << std::endl
					<< importer.GetErrorString() << std::endl;
				return new graphics::Model;
			}

			graphics::Model* model = new graphics::Model(assimpProcessNode(scene->mRootNode, scene, path));

			importer.FreeScene();

			return model;
		}

		std::vector<graphics::Mesh*> ModelLoader::assimpProcessNode(aiNode* node, const aiScene* scene, std::string path)
		{
			std::vector<graphics::Mesh*> meshes;

			for (GLuint i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(assimpProcessMesh(mesh, scene, path));
			}

			for (GLuint i = 0; i < node->mNumChildren; i++)
			{
				std::vector<graphics::Mesh*> childMeshes = assimpProcessNode(node->mChildren[i], scene, path);
				meshes.insert(meshes.end(), childMeshes.begin(), childMeshes.end());
			}

			return meshes;
		}

		graphics::Mesh* ModelLoader::assimpProcessMesh(aiMesh* mesh, const aiScene* scene, std::string path)
		{
			std::vector<graphics::Vertex> vertices;
			std::vector<GLuint> indices;
			std::vector<graphics::Texture*> textures;

			for (GLint i = 0; i < mesh->mNumVertices; ++i)
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

			for (GLint i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (int j = 0; j < face.mNumIndices; j++)
					indices.push_back((face.mIndices[j]));
			}

			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

			graphics::Material* myMaterial = new graphics::Material;

			if (mesh->mMaterialIndex >= 0)
			{
				std::map<graphics::TextureType, std::vector<graphics::Texture*>> textureMaps;

				assimpLoadMaterialTextures(material, aiTextureType_DIFFUSE, graphics::AlbedoMap, myMaterial, path);
				assimpLoadMaterialTextures(material, aiTextureType_SPECULAR, graphics::SpecularMap, myMaterial, path);
			}

			aiColor3D diffuse;
			material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
			myMaterial->setAlbedo(math::vec3(diffuse.r, diffuse.g, diffuse.b));

			aiColor3D specular;
			material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
			myMaterial->setSpecular(math::vec3(specular.r, specular.g, specular.b));

			GLfloat shininess;
			material->Get(AI_MATKEY_SHININESS, shininess);
			myMaterial->setGloss(shininess);

			return new graphics::Mesh(vertices, indices, myMaterial);
		}

		void ModelLoader::assimpLoadMaterialTextures(aiMaterial* material, aiTextureType type, graphics::TextureType bplrType, graphics::Material* myMaterial, std::string path)
		{
			if (material->GetTextureCount(type) > 0)
			{
				std::string directory = path.substr(0, path.find_last_of('/'));
				for (int i = 0; i < material->GetTextureCount(type); i++)
				{
					aiString string;
					material->GetTexture(type, i, &string);
//					GLboolean skip = false;

//					for (int j = 0; j < m_textures.size(); ++j)
//					{
//						if (m_textures[j]->getPath() == string)
//						{
//							textures.push_back(m_textures[j]);
//							skip = true;
//							break;
//						}
//					}
//					if (!skip)
//					{
						graphics::Texture* texture = new graphics::Texture((directory + "/" + string.C_Str()).c_str(), bplrType);
//						m_textures.push_back(texture);
						switch (bplrType)
						{
						case graphics::AlbedoMap:
							myMaterial->setAlbedoMap(texture);
							break;
						case graphics::SpecularMap:
							myMaterial->setSpecularMap(texture);
							break;
						case graphics::GlossMap:
							myMaterial->setGlossMap(texture);
							break;
						case graphics::NormalMap:
							myMaterial->setNormalMap(texture);
							break;
						default:
							break;
						}
//					}
				}
			}
		}
	}
}
