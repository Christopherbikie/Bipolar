#include "LightSourceComponent.h"
#include "TransformComponent.h"
#include "Component.h"
#include "../Entity.h"

namespace bplr
{
	namespace scene
	{
		LightSourceComponent::LightSourceComponent(math::vec3 colour, math::vec3 ambient)
			: m_colour(colour), m_ambient(ambient)
		{
		}

		math::vec3 LightSourceComponent::getColour() const
		{
			return m_colour;
		}

		void LightSourceComponent::setColour(const math::vec3& colour)
		{
			m_colour = colour;
		}

		math::vec3 LightSourceComponent::getAmbient() const
		{
			return m_ambient;
		}

		void LightSourceComponent::setAmbient(const math::vec3& ambient)
		{
			m_ambient = ambient;
		}

		void LightSourceComponent::loadUniforms(graphics::Shader* shader) const
		{
			shader->loadUniform("light.position", m_entity->getComponent<TransformComponent>()->position);
			shader->loadUniform("light.colour", m_colour);
			shader->loadUniform("light.ambient", m_ambient);
		}

		std::string LightSourceComponent::getType()
		{
			return getStaticType();
		}

		std::string LightSourceComponent::getStaticType()
		{
			return "LightSource";
		}
	}
}
