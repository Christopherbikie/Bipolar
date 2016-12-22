#pragma once

#include "Component.h"
#include "../../graphics/Mesh.h"
#include "../../graphics/Model.h"

namespace bplr
{
	namespace scene
	{
		class MeshComponent : public Component
		{
		public:
			MeshComponent(graphics::Model* model);
			~MeshComponent();

			void render(graphics::Shader3D* shader) const;

			std::string getType() override;
			static std::string getStaticType();

			graphics::Model* getModel() const;
			void setModel(graphics::Model* model);
			graphics::Mesh* getMesh(GLint index) const;

		private:
			graphics::Model* m_model;
		};
	}
}
