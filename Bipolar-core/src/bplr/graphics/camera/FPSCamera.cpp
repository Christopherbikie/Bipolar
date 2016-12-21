#include "FPSCamera.h"

namespace bplr
{
	namespace graphics
	{
		FPSCamera::FPSCamera(math::vec3 position, math::vec3 rotation, GLfloat fov, GLfloat aspectRatio)
			: Camera(position, rotation), m_fov(fov), m_aspectRatio(aspectRatio)
		{
			updateProjectionMatrix();
		}

		GLfloat FPSCamera::getFov() const
		{
			return m_fov;
		}

		void FPSCamera::setFov(GLfloat fov)
		{
			m_fov = fov;
			updateProjectionMatrix();
		}

		GLfloat FPSCamera::getAspectRatio() const
		{
			return m_aspectRatio;
		}

		void FPSCamera::setAspectRatio(GLfloat aspectRatio)
		{
			m_aspectRatio = aspectRatio;
			updateProjectionMatrix();
		}

		void FPSCamera::updateProjectionMatrix()
		{
			m_projMat = math::mat4::perspective(m_fov, m_aspectRatio, 0.5f, 1000.0f);
		}
	}
}
