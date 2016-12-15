#pragma once

#include "../../math/vec3.h"
#include "../../math/mat4.h"

namespace bplr
{
	namespace graphics
	{
		class Camera
		{
		public:
			Camera(math::vec3 position, math::vec3 rotation)
				: m_position(position), m_rotation(rotation)
			{
			}
			virtual ~Camera() {}

			math::mat4 getProjectionMatrix() const { return m_projMat; }
			math::mat4 Camera::getViewMatrix() const { return math::mat4(1.0f).translate(-m_position) * math::mat4(1.0f).rotate(m_rotation); }
			math::mat4 Camera::getViewMatrixNoTranslate() const { return math::mat4(1.0f).rotate(m_rotation); }

			math::vec3 getPosition() const { return m_position; }
			void setPosition(const math::vec3& position) { m_position = position; }
			math::vec3 getRotation() const { return m_rotation; }
			void setRotation(const math::vec3& rotation) { m_rotation = rotation; }

		protected:
			math::mat4 m_projMat;
			math::vec3 m_position;
			math::vec3 m_rotation;
		};
	}
}
