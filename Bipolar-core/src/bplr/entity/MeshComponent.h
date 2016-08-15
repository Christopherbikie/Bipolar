#pragma once

#include "Component.h"
#include "../graphics/VAO.h"

namespace bplr
{
	namespace entity
	{
		class MeshComponent : public Component
		{
		public:
			MeshComponent(graphics::VAO* vao);

			graphics::VAO* getVAO();
			void setVAO(graphics::VAO* vao);

			void render(graphics::Shader shader) const;

			std::string getType() override;
			static std::string getStaticType();
			
		private:
			graphics::VAO m_vao;
		};
	}
}
