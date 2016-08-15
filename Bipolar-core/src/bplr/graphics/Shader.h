#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>
#include "../math/vec2.h"
#include "../math/vec3.h"
#include "../math/vec4.h"
#include "../math/mat4.h"

namespace bplr
{
	namespace graphics
	{
		enum ShaderType
		{
			VERTEX_SHADER = GL_VERTEX_SHADER,
			TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
			TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
			GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
			FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
		};
		extern const std::map<GLuint, GLchar*> shaderTypeNames;

		class Shader
		{
		public:
			Shader();
			~Shader();

			void addSource(ShaderType type, const GLchar* path);
			void link();
			void use() const;

			void loadUniform(std::string name, GLboolean value) const;
			void loadUniform(std::string name, GLint value) const;
			void loadUniform(std::string name, GLfloat value) const;
			void loadUniform(std::string name, GLdouble value) const;
			void loadUniform(std::string name, math::vec2 vector) const;
			void loadUniform(std::string name, math::vec3 vector) const;
			void loadUniform(std::string name, math::vec4 vector) const;
			void loadUniform(std::string name, math::mat4 matrix) const;

			void drawArrays(GLint first, GLint count) const;
			void drawElements(GLint count);

			GLuint getLocation() const;
		
		private:
			GLuint m_program;
			std::vector<GLuint> m_shaders;
		};
	}
}
