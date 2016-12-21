#pragma once

#include "Component.h"
#include "../../graphics/Mesh.h"
#include "../../graphics/Model.h"

namespace bplr
{
	namespace entity
	{
		class MeshComponent : public Component
		{
		public:
			MeshComponent(graphics::Model* model);
			~MeshComponent();

			void render(graphics::Shader3D* shader) const;

			std::string getType() override;
			static std::string getStaticType();

		private:
			graphics::Model* m_model;
		};
	}
}
