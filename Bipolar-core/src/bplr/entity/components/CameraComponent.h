#pragma once

#include "Component.h"
#include "../../math/mat4.h"
#include "TransformComponent.h"

namespace bplr
{
	namespace entity
	{
		class CameraComponent : public Component
		{
		public:
			void update(float delta) const;
			math::mat4 getViewMatrix() const;
			math::mat4 getViewMatrixNoTranslate() const;

			std::string getType() override;
			static std::string getStaticType();
			void setEntity(Entity* entity) override;
			
		private:
			TransformComponent* m_transform;
			float m_moveSpeed = 3.0f, m_sensitivity = 1.0f / 5;
		};
	}
}
