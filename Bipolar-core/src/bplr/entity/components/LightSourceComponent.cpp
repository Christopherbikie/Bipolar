#include "LightSourceComponent.h"

namespace bplr
{
	namespace entity
	{
		LightSourceComponent::LightSourceComponent(math::vec3 colour)
			: m_colour(colour)
		{
		}

		math::vec3 LightSourceComponent::getColour() const
		{
			return m_colour;
		}

		void LightSourceComponent::setColour(math::vec3 colour)
		{
			m_colour = colour;
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
