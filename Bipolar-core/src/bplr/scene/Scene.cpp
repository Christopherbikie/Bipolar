#include <iostream>
#include <algorithm>
#include <functional>
#include "Scene.h"
#include "component/CameraComponent.h"
#include "component/LightSourceComponent.h"
#include "../graphics/Shader.h"
#include "../graphics/CubeMap.h"
#include "component/MeshComponent.h"

namespace bplr
{
	namespace scene
	{
		Scene::Scene()
			: m_camera(nullptr)
		{
		}

		Scene::~Scene()
		{
			m_entities.clear();
			m_entitiesToAdd.clear();
		}

		void Scene::addEntity(std::shared_ptr<Entity> entity)
		{
			m_entitiesToAdd.push_back(entity);
		}

		void Scene::addLight(std::shared_ptr<Entity> light)
		{
			LightSourceComponent* lightSourceComponent = light->getComponent<LightSourceComponent>();
			if (lightSourceComponent == nullptr)
			{
				std::cout << "Attempted to add an Entity without a LightSourceComponent to a scene's lights" << std::endl;
				return;
			}
			m_lightsToAdd.push_back(light);
		}

		void Scene::setCamera(Entity* newCameraEntity)
		{
			CameraComponent* cameraComponent = newCameraEntity->getComponent<CameraComponent>();
			if (cameraComponent == nullptr)
			{
				std::cout << "Attempted to set an Entity without a CameraComponent as a scene's camera" << std::endl;
				return;
			}
			m_camera = cameraComponent->getCamera();
		}

		Camera* Scene::getCamera() const
		{
			return m_camera;
		}

		void Scene::setEnvMap(graphics::CubeMap* cubeMap)
		{
			m_envMap = cubeMap;
		}

		void Scene::render(graphics::Shader3D* shader)
		{
			shader->use();
			shader->loadUniform("view", m_camera->getViewMatrix());
			shader->loadUniform("projection", m_camera->getProjectionMatrix());
			shader->loadUniform("cameraPosition", m_camera->getPosition());

			for (std::shared_ptr<Entity> light : m_lights)
			{
				light->getComponent<LightSourceComponent>()->loadUniforms(shader);
				break;
			}

			if (m_envMap != nullptr)
				m_envMap->bind();

			for (std::shared_ptr<Entity> entity : m_entities)
			{
				shader->loadUniform("model", entity->getComponent<TransformComponent>()->getTransform());
				entity->getComponent<MeshComponent>()->render(shader);
			}
		}

		void Scene::post()
		{
			m_entities.erase(remove_if(m_entities.begin(), m_entities.end(), std::mem_fn(&Entity::isDestroyed)), m_entities.end());

			m_entities.insert(m_entities.end(), make_move_iterator(m_entitiesToAdd.begin()), make_move_iterator(m_entitiesToAdd.end()));
			m_entitiesToAdd.clear();

			m_lights.erase(remove_if(m_lights.begin(), m_lights.end(), std::mem_fn(&Entity::isDestroyed)), m_lights.end());

			m_lights.insert(m_lights.end(), make_move_iterator(m_lightsToAdd.begin()), make_move_iterator(m_lightsToAdd.end()));
			m_lightsToAdd.clear();
		}
	}
}
