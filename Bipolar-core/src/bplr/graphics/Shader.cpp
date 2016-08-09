#include "Shader.h"
#include "../util/Loader.h"
#include <iostream>

namespace bplr
{
	namespace graphics
	{
		const std::map<GLuint, GLchar*> shaderTypeNames {
			{GL_VERTEX_SHADER, "vertex"},
			{GL_TESS_CONTROL_SHADER, "tesselation control"},
			{GL_TESS_EVALUATION_SHADER, "tesselation evaluation"},
			{GL_GEOMETRY_SHADER, "geometry"},
			{GL_FRAGMENT_SHADER, "fragment"},
		};

		Shader::Shader()
		{
			m_program = glCreateProgram();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_program);
		}

		void Shader::addSource(ShaderType type, const GLchar* path)
		{
			std::string shaderSourceStdString = util::loadFileAsString(path);
			const GLchar* shaderSource = shaderSourceStdString.c_str();

			GLuint shaderLocation = glCreateShader(type);
			glShaderSource(shaderLocation, 1, &shaderSource, NULL);
			glCompileShader(shaderLocation);

			GLchar infolog[512];
			GLint success;
			glGetShaderiv(shaderLocation, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shaderLocation, 512, NULL, infolog);
				std::cout << "Failed to compile " << shaderTypeNames.at(static_cast<GLuint>(type)) << " shader at \"" << path << "\"\n" << infolog << std::endl;
			}

			glAttachShader(m_program, shaderLocation);
			m_shaders.push_back(shaderLocation);
		}

		void Shader::link()
		{
			glLinkProgram(m_program);

			GLchar infolog[512];
			GLint success;
			glGetProgramiv(m_program, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(m_program, 512, NULL, infolog);
				std::cout << "Failed to link program\n" << infolog << std::endl;
			}

			for (GLuint shader : m_shaders)
			{
				glDetachShader(m_program, shader);
				glDeleteShader(shader);
			}
		}

		void Shader::use() const
		{
			glUseProgram(m_program);
		}

		void Shader::drawArrays(GLint first, GLint count) const
		{
			glDrawArrays(GL_TRIANGLES, first, count);
		}

		void Shader::drawElements(GLint count)
		{
			glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
		}

		GLuint Shader::getLocation() const
		{
			return m_program;
		}
	}
}
