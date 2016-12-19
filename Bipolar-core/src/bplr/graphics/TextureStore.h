#pragma once

#include <vector>
#include <map>

namespace bplr
{
	namespace graphics
	{
		class Texture;

		class TextureStore
		{
		public:
			static void add(Texture* texture);
			static Texture* get(std::string path);

			static void clear();

			static std::vector<std::string> getTexturePaths();

		private:
			static std::map<std::string, Texture*> m_textures;
		};
	}
}
