#include "Material.h"
#include <functional>

namespace bplr
{
	namespace graphics
	{
		Material::Material()
		{
			m_blankTexture = new Texture(1, 1);
		}

		Material::~Material()
		{
			delete m_blankTexture;
		}

		void Material::loadUniforms(Shader* shader, std::string structName) const
		{
			glActiveTexture(GL_TEXTURE0);
			if (m_albedoMap != nullptr)
			{
				m_albedoMap->bind(shader, (structName + ".albedoMap").c_str());
				shader->loadUniform((structName + ".usingAlbedoMap").c_str(), 1.0f);
			}
			else
			{
				m_blankTexture->bind(shader, (structName + ".albedoMap").c_str());
				shader->loadUniform((structName + ".usingAlbedoMap").c_str(), 0.0f);
			}

			glActiveTexture(GL_TEXTURE1);
			if (m_glossMap != nullptr)
			{
				m_glossMap->bind(shader, (structName + ".glossMap").c_str());
				shader->loadUniform((structName + ".usingGlossMap").c_str(), 1.0f);
			}
			else
			{
//				glActiveTexture(GL_TEXTURE1);
//				m_blankTexture->bind(shader, (structName + ".glossMap").c_str());
				shader->loadUniform((structName + ".usingGlossMap").c_str(), 0.0f);
			}

			glActiveTexture(GL_TEXTURE2);
			if (m_normalMap != nullptr)
			{
				m_normalMap->bind(shader, (structName + ".normalMap").c_str());
				shader->loadUniform((structName + ".usingNormalMap").c_str(), 1.0f);
			}
			else
			{
				m_blankTexture->bind(shader, (structName + ".normalMap").c_str());
				shader->loadUniform((structName + ".usingNormalMap").c_str(), 0.0f);
			}

			glActiveTexture(GL_TEXTURE3);
			if (m_specularMap != nullptr)
			{
				m_specularMap->bind(shader, (structName + ".specularMap").c_str());
				shader->loadUniform((structName + ".usingSpecularMap").c_str(), 1.0f);
			}
			else
			{
				m_blankTexture->bind(shader, (structName + ".specularMap").c_str());
				shader->loadUniform((structName + ".usingSpecularMap").c_str(), 0.0f);
			}

			shader->loadUniform(structName + ".albedo", m_albedo);
			shader->loadUniform(structName + ".specular", m_specular);
			shader->loadUniform(structName + ".gloss", m_gloss);
		}

		void Material::unbindTextures() const
		{
			m_albedoMap->unbind();
			m_glossMap->unbind();
			m_normalMap->unbind();
			m_specularMap->unbind();
			m_blankTexture->unbind();
		}

		void Material::setAlbedo(const math::vec3& albedo)
		{
			m_albedo = albedo;
		}

		void Material::setSpecular(const math::vec3& specular)
		{
			m_specular = specular;
		}

		void Material::setGloss(GLfloat gloss)
		{
			m_gloss = gloss;
		}

		void Material::setAlbedoMap(Texture* albedoMap)
		{
			m_albedoMap = albedoMap;
		}

		void Material::setGlossMap(Texture* glossMap)
		{
			m_glossMap = glossMap;
		}

		void Material::setNormalMap(Texture* normalMap)
		{
			m_normalMap = normalMap;
		}

		void Material::setSpecularMap(Texture* specularMap)
		{
			m_specularMap = specularMap;
		}
	}
}
