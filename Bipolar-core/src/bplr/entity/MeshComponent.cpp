#include "MeshComponent.h"
#include "../graphics/VAO.h"

namespace bplr
{
	namespace entity
	{
		MeshComponent::MeshComponent(graphics::VAO* vao)
			: m_vao(*vao)
		{
		}

		graphics::VAO* MeshComponent::getVAO()
		{
			return &m_vao;
		}

		void MeshComponent::setVAO(graphics::VAO* vao)
		{
			m_vao = *vao;
		}

		void MeshComponent::render(graphics::Shader shader) const
		{
			shader.use();
			m_vao.bind();
			m_vao.bindEBO();
			shader.drawElements(m_vao.getVertexCount());
			m_vao.unbind();
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
