#include "TransformComponent.h"
#include <GL/glew.h>
#include "../../math/mat4.h"

namespace bplr
{
	namespace entity
	{
		TransformComponent::TransformComponent(math::vec3 position)
			: position(position)
		{
		}

		TransformComponent::TransformComponent(math::vec3 position, math::vec3 rotation)
			: position(position), rotation(rotation)
		{
		}

		TransformComponent::TransformComponent(math::vec3 position, GLfloat scale)
			: position(position), scale(scale)
		{
		}

		TransformComponent::TransformComponent(math::vec3 position, math::vec3 rotation, GLfloat scale)
			:position(position), rotation(rotation), scale(scale)
		{
		}

		TransformComponent::TransformComponent(math::vec3 position, math::vec3 rotation, math::vec3 scale)
			: position(position), rotation(rotation), scale(scale)
		{
		}

		math::mat4 TransformComponent::getTransform() const
		{
			return math::mat4::identity() * math::mat4::scale(scale) * math::mat4::rotate(rotation) * math::mat4::translate(position);
		}

		std::string TransformComponent::getType()
		{
			return getStaticType();
		}

		std::string TransformComponent::getStaticType()
		{
			return "Transform";
		}
	}
}
