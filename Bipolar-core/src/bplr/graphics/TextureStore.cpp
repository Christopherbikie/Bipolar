#include "TextureStore.h"
#include "Texture.h"

namespace bplr
{
	namespace graphics
	{
		std::map<std::string, Texture*> TextureStore::m_textures;

		void TextureStore::add(Texture* texture)
		{
			m_textures[texture->getPath()] = texture;
		}

		Texture* TextureStore::get(std::string path)
		{
			if (m_textures.find(path) == m_textures.end())
				return nullptr;
			return m_textures[path];
		}

		void TextureStore::clear()
		{
			for (std::pair<std::string, Texture*> texture : m_textures)
				delete texture.second;
			m_textures.clear();
		}

		std::vector<std::string> TextureStore::getTexturePaths()
		{
			std::vector<std::string> paths;
			for (std::pair<std::string, Texture*> texture : m_textures)
				paths.push_back(texture.first);
			return paths;
		}
	}
}
