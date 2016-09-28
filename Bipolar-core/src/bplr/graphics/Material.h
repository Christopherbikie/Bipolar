#pragma once
#include "Texture.h"

namespace bplr
{
	namespace graphics
	{
		class Material
		{
		public:
			Material();
			Material(const char* path);
			~Material();

			void loadUniforms(Shader* shader, std::string structName = "material") const;

			void setAlbedo(const math::vec3& albedo);
			void setSpecular(const math::vec3& specular);
			void setGloss(GLfloat gloss);
			void setAlbedoMap(Texture* albedoMap);
			void setGlossMap(Texture* glossMap);
			void setNormalMap(Texture* normalMap);
			void setSpecularMap(Texture* specularMap);

		private:
			math::vec3 m_albedo = math::vec3(1.0f);
			math::vec3 m_specular = math::vec3();
			GLfloat m_gloss = 0.0f;

			Texture* m_albedoMap;
			Texture* m_glossMap;
			Texture* m_normalMap;
			Texture* m_specularMap;
		};
	}
}
