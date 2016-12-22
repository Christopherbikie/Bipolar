#pragma once

#include <memory>
#include "Entity.h"
#include "camera/Camera.h"

namespace bplr
{
	namespace graphics
	{
		class Shader3D;
		class CubeMap;
	}

	namespace scene
	{
		class Scene
		{
		public:
			Scene();
			~Scene();

			void addEntity(std::shared_ptr<Entity> entity);
			void addLight(std::shared_ptr<Entity> light);

			void setCamera(Entity* newCameraEntity);
			Camera* getCamera() const;

			void setEnvMap(graphics::CubeMap* cubeMap);

			void update(GLfloat delta);
			void render(graphics::Shader3D* shader);
			void post();

		private:
			std::vector<std::shared_ptr<Entity>> m_entities;
			std::vector<std::shared_ptr<Entity>> m_entitiesToAdd;
			std::vector<std::shared_ptr<Entity>> m_lights;
			std::vector<std::shared_ptr<Entity>> m_lightsToAdd;

			Camera* m_camera;
			graphics::CubeMap* m_envMap;
		};
	}
}
