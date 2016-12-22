#include "MeshComponent.h"

namespace bplr
{
	namespace scene
	{
		MeshComponent::MeshComponent(graphics::Model* model)
			: m_model(model)
		{
		}

		MeshComponent::~MeshComponent()
		{
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

		graphics::Model* MeshComponent::getModel() const
		{
			return m_model;
		}

		void MeshComponent::setModel(graphics::Model* model)
		{
			m_model = model;
		}

		graphics::Mesh* MeshComponent::getMesh(GLint index) const
		{
			return m_model->getMeshes()[index];
		}
	}
}
