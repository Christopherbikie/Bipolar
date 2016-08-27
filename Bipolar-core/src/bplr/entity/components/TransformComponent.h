#pragma once

#include "Component.h"
#include "../../math/vec3.h"
#include <GL/glew.h>

namespace bplr
{
	namespace entity
	{
		class TransformComponent : public Component
		{
		public:
			TransformComponent(math::vec3 position);
			TransformComponent(math::vec3 position, math::vec3 rotation);
			TransformComponent(math::vec3 position, GLfloat scale);
			TransformComponent(math::vec3 position, math::vec3 rotation, GLfloat scale);
			TransformComponent(math::vec3 position, math::vec3 rotation, math::vec3 scale);

			math::vec3 position;
			math::vec3 rotation = math::vec3(0.0f);
			math::vec3 scale = math::vec3(1.0f);

			math::mat4 getTransform() const;

			std::string getType() override;
			static std::string getStaticType();
		};
	}
}
