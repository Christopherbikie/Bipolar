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

		ShaderSource::ShaderSource(ShaderType type, std::string path)
			: type(type), path(path)
		{
		}

		bool ShaderSource::operator==(const ShaderSource& other) const
		{
			return path == other.path;
		}

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
			if (m_linked)
			{
				std::cout << "Could not add source located at " << path << " to program, program is already linked!" << std::endl;
				return;
			}
			
			ShaderSource source = ShaderSource(type, path);
			if (!(std::find(m_sources.begin(), m_sources.end(), source) != m_sources.end()))
				m_sources.push_back(source);

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
			if (m_linked)
			{
				std::cout << "Could not link program, program is already linked!" << std::endl;
				return;
			}

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

			m_linked = true;

			postLink();
		}

		void Shader::use() const
		{
			glUseProgram(m_program);
		}

		void Shader::reload()
		{
			glDeleteProgram(m_program);
			m_program = glCreateProgram();
			m_linked = false;

			for (ShaderSource source : m_sources)
				this->addSource(source.type, source.path.c_str());
			
			this->link();
		}

		void Shader::loadUniform(std::string name, GLboolean value) const
		{
			GLuint uniformLocation = glGetUniformLocation(m_program, name.c_str());
			glUniform1i(uniformLocation, value ? 1 : 0);
		}

		void Shader::loadUniform(std::string name, GLint value) const
		{
			GLuint uniformLocation = glGetUniformLocation(m_program, name.c_str());
			glUniform1i(uniformLocation, value);
		}

		void Shader::loadUniform(std::string name, GLfloat value) const
		{
			GLuint uniformLocation = glGetUniformLocation(m_program, name.c_str());
			glUniform1f(uniformLocation, value);
		}

		void Shader::loadUniform(std::string name, GLdouble value) const
		{
			GLuint uniformLocation = glGetUniformLocation(m_program, name.c_str());
			glUniform1d(uniformLocation, value);
		}

		void Shader::loadUniform(std::string name, math::vec2 vector) const
		{
			GLuint uniformLocation = glGetUniformLocation(m_program, name.c_str());
			glUniform2f(uniformLocation, vector.x, vector.y);
		}

		void Shader::loadUniform(std::string name, math::vec3 vector) const
		{
			GLuint uniformLocation = glGetUniformLocation(m_program, name.c_str());
			glUniform3f(uniformLocation, vector.x, vector.y, vector.z);
		}

		void Shader::loadUniform(std::string name, math::vec4 vector) const
		{
			GLuint uniformLocation = glGetUniformLocation(m_program, name.c_str());
			glUniform4f(uniformLocation, vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::loadUniform(std::string name, math::mat4 matrix) const
		{
			GLuint uniformLocation = glGetUniformLocation(m_program, name.c_str());
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, matrix.elements);
		}

		GLuint Shader::getLocation() const
		{
			return m_program;
		}

		void Shader::postLink()
		{
		}
	}
}
