#include "CubeMap.h"
#include <iostream>
#include "Texture.h"
#include "Shader3D.h"

namespace bplr
{
	namespace graphics
	{
		CubeMap::CubeMap(std::string right, std::string left, std::string top, std::string bottom, std::string back, std::string front)
		{
			std::vector<std::string> faces;
			faces.push_back(right);
			faces.push_back(left);
			faces.push_back(top);
			faces.push_back(bottom);
			faces.push_back(back);
			faces.push_back(front);

			glGenTextures(1, &m_location);
			glActiveTexture(GL_TEXTURE0);

			glBindTexture(GL_TEXTURE_CUBE_MAP, m_location);
			for (GLuint i = 0; i < faces.size(); i++)
				new Texture(faces[i], GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			GLfloat cubeMapVertices[] = {
				-1.0f,  1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,
				1.0f, -1.0f, -1.0f,
				1.0f, -1.0f, -1.0f,
				1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f, -1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				1.0f, -1.0f, -1.0f,
				1.0f, -1.0f,  1.0f,
				1.0f,  1.0f,  1.0f,
				1.0f,  1.0f,  1.0f,
				1.0f,  1.0f, -1.0f,
				1.0f, -1.0f, -1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				1.0f,  1.0f,  1.0f,
				1.0f,  1.0f,  1.0f,
				1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,

				-1.0f,  1.0f, -1.0f,
				1.0f,  1.0f, -1.0f,
				1.0f,  1.0f,  1.0f,
				1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f, -1.0f,

				-1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				1.0f, -1.0f, -1.0f,
				1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				1.0f, -1.0f,  1.0f
			};

			m_vao = new VAO();
			m_vao->storeInBuffer(0, 3, 36, cubeMapVertices);
		}

		CubeMap::~CubeMap()
		{
			glDeleteTextures(1, &m_location);
			delete m_vao;
		}

		void CubeMap::render(Shader3D* shader) const
		{
			glDepthMask(GL_FALSE);
			shader->use();
			m_vao->bind();
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(glGetUniformLocation(shader->getLocation(), "skybox"), 0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_location);
			shader->drawArrays(0, m_vao->getVertexCount());
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			m_vao->unbind();
			glDepthMask(GL_TRUE);
		}

		void CubeMap::bind() const
		{
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_location);
		}
	}
}
