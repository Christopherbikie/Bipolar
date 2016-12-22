#pragma once

#include <vector>
#include <GL/glew.h>
#include "component/Component.h"

namespace bplr
{
	namespace scene
	{
		class Entity
		{
		public:
			Entity();
			~Entity();

			void update(GLfloat delta);

			Entity* addComponent(Component *c);
			template <typename T>
			T* getComponent();
			std::vector<Component*> getComponents() const;
			void destroy();
			bool isDestroyed() const;

		private:
			std::vector<Component*> m_components;
			bool m_destroyed;

			template <typename T>
			const T* Entity::getComponentInternal() const
			{
				std::string type = T::getStaticType();
				for (Component* component : m_components)
				{
					if (component->getType() == type)
						return (T*) component;
				}
				return nullptr;
			}
		};

		template <typename T>
		T* Entity::getComponent()
		{
			return (T*) getComponentInternal<T>();
		}
	}
}
