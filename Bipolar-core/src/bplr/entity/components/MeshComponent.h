#pragma once

#include "Component.h"
#include "../../graphics/Mesh.h"

namespace bplr
{
	namespace entity
	{
		class MeshComponent : public Component
		{
		public:
			MeshComponent(graphics::Mesh* mesh);
			~MeshComponent();

			void addMesh(graphics::Mesh* mesh);

			void render(graphics::Shader3D* shader) const;

			std::string getType() override;
			static std::string getStaticType();
			
		private:
			std::vector<graphics::Mesh*> m_meshes;
		};
	}
}
