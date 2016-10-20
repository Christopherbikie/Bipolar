#include "MeshComponent.h"

namespace bplr
{
	namespace entity
	{
		MeshComponent::MeshComponent(graphics::Mesh* mesh)
		{
			m_meshes.push_back(mesh);
		}

		MeshComponent::~MeshComponent()
		{
			for (graphics::Mesh* mesh : m_meshes)
				delete mesh;
		}

		void MeshComponent::addMesh(graphics::Mesh* mesh)
		{
			m_meshes.push_back(mesh);
		}

		void MeshComponent::render(graphics::Shader3D *shader) const
		{
			for (graphics::Mesh* mesh : m_meshes)
				mesh->render(shader);
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
