#include "MeshComponent.h"

namespace bplr
{
	namespace entity
	{
		MeshComponent::MeshComponent(graphics::Model* model)
			: m_model(model)
		{
		}

		MeshComponent::~MeshComponent()
		{
			delete m_model;
		}

		void MeshComponent::render(graphics::Shader3D *shader) const
		{
			m_model->render(shader);
		}

		std::string MeshComponent::getType()
		{
			return getStaticType();
		}

		std::string MeshComponent::getStaticType()
		{
			return "Mesh";
		}
	}
}
