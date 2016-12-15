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

			virtual math::mat4 getProjectionMatrix() const = 0;
			virtual math::mat4 getViewMatrix() const = 0;
			virtual math::mat4 getViewMatrixNoTranslate() const = 0;


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
