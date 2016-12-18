#pragma once

#include <map>
#include <vector>
#include <GL/glew.h>
#include "FreeImage.h"
#include "Shader.h"

namespace bplr
{
	namespace graphics
	{
		enum TextureType
		{
			Unknown,
			AlbedoMap,
			GlossMap,
			NormalMap,
			SpecularMap,
		};

		static std::map<TextureType, std::string> typeNames = {
			{ AlbedoMap, "albedo" },
			{ Unknown, "unknown" },
			{ GlossMap, "gloss" },
			{ NormalMap, "normal" },
			{ SpecularMap, "specular" },
		};

		class Texture
		{
		public:
			Texture(std::string path);
			// For loading cubemap faces
			Texture(std::string path, GLenum cubemapFace);
//			Texture(GLuint width, GLuint height, unsigned char *data);
			~Texture();

			void bind(Shader *shader, const char *uniformName) const;

		private:
			GLuint m_location;
			std::string m_path;
			GLuint m_width, m_height;
			FIBITMAP *m_bitmap, *m_bitmap32;

			GLubyte* loadToBitmap(std::string path, bool flip = false);
		};

//		class TextureStore
//		{
//		public:
//			static void init();
//
//			static void add(Texture* model);
//			static Texture* get(std::string path);
//			static Texture* getBlank();
//
//			static void clear();
//
//			static std::vector<std::string> getTexturePaths();
//
//		private:
//			static std::map<std::string, Texture*> m_textures;
//			static GLboolean m_initialised;
//		};
	}
}
