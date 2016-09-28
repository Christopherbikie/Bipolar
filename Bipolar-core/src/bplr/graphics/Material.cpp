#include "Material.h"
#include <fstream>
#include <iostream>
#include <functional>
#include <locale>
#include <sstream>

namespace bplr
{
	namespace graphics
	{
		Material::Material()
		{
		}

		Material::Material(std::string path)
		{
			std::ifstream matFile(path);
			
			if (!matFile.is_open())
				std::cout << "Failed to open material file at " << path << std::endl;

			GLint lineNumber = 0;
			std::string line;
			while (getline(matFile, line))
			{
				lineNumber++;

				// Trim leading whitespace (trailing whitespace does not matter)
				std::string::iterator iterator = std::find_if(line.begin(), line.end(), [](GLchar ch)
				{
					return !std::isspace<GLchar>(ch, std::locale::classic());
				});
				line.erase(line.begin(), iterator);

				if (line == "")
					continue;

				// Split line at each space char
				std::vector<std::string> lineWords;
				std::stringstream ss(line);
				std::string tok;
				while (getline(ss, tok, ' ')) {
					lineWords.push_back(tok);
				}

				std::string statement = lineWords[0];

				if (statement == "#")
					continue;

				if (statement == "albedo")
				{
					if (lineWords.size() < 4)
					{
						std::cout << "Malformated material file at \"" << path << "\" on line " << lineNumber
							<< ": Not enough arguments (found " << lineWords.size() - 1 << ", expected 3)" << std::endl;
						continue;
					}
					GLfloat r = stof(lineWords[1]);
					GLfloat g = stof(lineWords[2]);
					GLfloat b = stof(lineWords[3]);
					m_albedo = math::vec3(r, g, b);
				}
				else if (statement == "specular")
				{
					if (lineWords.size() < 4)
					{
						std::cout << "Malformated material file at \"" << path << "\" on line " << lineNumber
							<< ": Not enough arguments (found " << lineWords.size() - 1 << ", expected 3)" << std::endl;
						continue;
					}
					GLfloat r = stof(lineWords[1]);
					GLfloat g = stof(lineWords[2]);
					GLfloat b = stof(lineWords[3]);
					m_specular = math::vec3(r, g, b);
				}
				else if (statement == "gloss")
				{
					if (lineWords.size() < 2)
					{
						std::cout << "Malformated material file at \"" << path << "\" on line " << lineNumber
							<< ": No arguments found (expected 1)" << std::endl;
						continue;
					}
					GLfloat value = stof(lineWords[1]);
					m_gloss = value;
				}
				else if (statement == "albedoMap")
				{
					if (lineWords.size() < 2)
					{
						std::cout << "Malformated material file at \"" << path << "\" on line " << lineNumber
							<< ": No arguments found (expected 1)" << std::endl;
						continue;
					}
					std::string path = lineWords[1];
					m_albedoMap = new Texture(path.c_str(), AlbedoMap);
				}
				else if (statement == "glossMap")
				{
					if (lineWords.size() < 2)
					{
						std::cout << "Malformated material file at \"" << path << "\" on line " << lineNumber
							<< ": No arguments found (expected 1)" << std::endl;
						continue;
					}
					std::string path = lineWords[1];
					m_glossMap = new Texture(path.c_str(), GlossMap);
				}
				else if (statement == "normalMap")
				{
					if (lineWords.size() < 2)
					{
						std::cout << "Malformated material file at \"" << path << "\" on line " << lineNumber
							<< ": No arguments found (expected 1)" << std::endl;
						continue;
					}
					std::string path = lineWords[1];
					m_normalMap = new Texture(path.c_str(), NormalMap);
				}
				else if (statement == "specularMap")
				{
					if (lineWords.size() < 2)
					{
						std::cout << "Malformated material file at \"" << path << "\" on line " << lineNumber
							<< ": No arguments found (expected 1)" << std::endl;
						continue;
					}
					std::string path = lineWords[1];
					m_specularMap = new Texture(path.c_str(), SpecularMap);
				}
			}

			matFile.close();
		}

		Material::~Material()
		{
			delete m_albedoMap;
			delete m_glossMap;
			delete m_normalMap;
			delete m_specularMap;
		}

		void Material::loadUniforms(Shader* shader, std::string structName) const
		{
			if (m_albedoMap != nullptr)
			{
				glActiveTexture(GL_TEXTURE0);
				m_albedoMap->bind(shader, (structName + ".albedoMap").c_str());
			}
			if (m_glossMap != nullptr)
			{
				glActiveTexture(GL_TEXTURE1);
				m_glossMap->bind(shader, (structName + ".glossMap").c_str());
			}
			if (m_normalMap != nullptr)
			{
				glActiveTexture(GL_TEXTURE2);
				m_normalMap->bind(shader, (structName + ".normalMap").c_str());
			}
			if (m_specularMap != nullptr)
			{
				glActiveTexture(GL_TEXTURE3);
				m_specularMap->bind(shader, (structName + ".specularMap").c_str());
			}

			shader->loadUniform(structName + ".albedo", m_albedo);
			shader->loadUniform(structName + ".specular", m_specular);
			shader->loadUniform(structName + ".gloss", m_gloss);
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
