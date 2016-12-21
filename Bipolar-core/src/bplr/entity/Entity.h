#pragma once

#include <vector>
#include "components/Component.h"

namespace bplr
{
	namespace entity
	{
		class Entity
		{
		public:
			Entity();
			~Entity();

			Entity* addComponent(Component *c);
			template <typename T>
			T* getComponent();
			std::vector<Component*> getComponents() const;

		private:
			std::vector<Component*> m_components;

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
