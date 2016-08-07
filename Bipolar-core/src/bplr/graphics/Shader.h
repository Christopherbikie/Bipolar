#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>

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
			void draw(GLint first, GLint count) const;

			GLuint getLocation() const;
		
		private:
			GLuint m_program;
			std::vector<GLuint> m_shaders;
		};
	}
}
