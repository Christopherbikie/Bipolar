#include <GL/glew.h>
#include "CameraComponent.h"
#include "../../input/Keyboard.h"
#include "../Entity.h"
#include "TransformComponent.h"
#include "../../input/Mouse.h"
#include "../../math/Math.h"

namespace bplr
{
	namespace entity
	{
		void CameraComponent::update(float delta) const
		{
			// Rotation
			if (input::Mouse::isCaptured())
			{
				math::vec2 mouseDiff = input::Mouse::getMovement() * m_sensitivity;
				m_transform->rotation += math::vec3(-mouseDiff.y, -mouseDiff.x, 0.0f);
			}

			// Position
			if (input::Keyboard::isKeyDown(GLFW_KEY_W))
			{
				m_transform->position.x -= sin(m_transform->rotation.y * math::PI / 180) * delta * m_moveSpeed;
				m_transform->position.y += sin(m_transform->rotation.x * math::PI / 180) * delta * m_moveSpeed;
				m_transform->position.z -= cos(m_transform->rotation.y * math::PI / 180) * delta * m_moveSpeed;
			}
			if (input::Keyboard::isKeyDown(GLFW_KEY_S))
			{
				m_transform->position.x += sin(m_transform->rotation.y * math::PI / 180) * delta * m_moveSpeed;
				m_transform->position.y -= sin(m_transform->rotation.x * math::PI / 180) * delta * m_moveSpeed;
				m_transform->position.z += cos(m_transform->rotation.y * math::PI / 180) * delta * m_moveSpeed;
			}
			if (input::Keyboard::isKeyDown(GLFW_KEY_A))
			{
				m_transform->position.x += sin((m_transform->rotation.y - 90) * math::PI / 180) * delta * m_moveSpeed;
				m_transform->position.z += cos((m_transform->rotation.y - 90) * math::PI / 180) * delta * m_moveSpeed;
			}
			if (input::Keyboard::isKeyDown(GLFW_KEY_D))
			{
				m_transform->position.x += sin((m_transform->rotation.y + 90) * math::PI / 180) * delta * m_moveSpeed;
				m_transform->position.z += cos((m_transform->rotation.y + 90) * math::PI / 180) * delta * m_moveSpeed;
			}
			if (input::Keyboard::isKeyDown(GLFW_KEY_SPACE))
				m_transform->position.y += delta * m_moveSpeed;
			if (input::Keyboard::isKeyDown(GLFW_KEY_LEFT_SHIFT))
				m_transform->position.y -= delta * m_moveSpeed;
		}

		math::mat4 CameraComponent::getViewMatrix() const
		{
			return math::mat4(1.0f).translate(-m_transform->position) * math::mat4(1.0f).rotate(m_transform->rotation);
		}

		math::mat4 CameraComponent::getViewMatrixNoTranslate() const
		{
			return math::mat4(1.0f).rotate(m_transform->rotation);
		}

		std::string CameraComponent::getType()
		{
			return getStaticType();
		}

		std::string CameraComponent::getStaticType()
		{
			return "Camera";
		}

		void CameraComponent::setEntity(Entity* entity)
		{
			m_entity = entity;
			m_transform = m_entity->getComponent<TransformComponent>();
		}
	}
}
