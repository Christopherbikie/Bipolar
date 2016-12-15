#pragma once

#include "Camera.h"
#include <GL/glew.h>

namespace bplr
{
	namespace graphics
	{
		class FPSCamera : public Camera
		{
		public:
			FPSCamera(math::vec3 position, math::vec3 rotation, GLfloat fov = 60.0f, GLfloat aspectRatio = 16.0f / 9.0f);

			GLfloat getFov() const;
			void setFov(GLfloat fov);
			GLfloat getAspectRatio() const;
			void setAspectRatio(GLfloat aspectRatio);

		private:
			GLfloat m_fov, m_aspectRatio, m_near, m_far;

			void updateProjectionMatrix();
		};
	}
}
