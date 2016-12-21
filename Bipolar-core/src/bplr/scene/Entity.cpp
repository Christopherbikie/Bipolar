#include "Entity.h"

namespace bplr
{
	namespace scene
	{
		Entity::Entity()
		{
		}

		Entity::~Entity()
		{
			for (Component* component : m_components)
			{
				delete component;
			}
		}

		Entity* Entity::addComponent(Component* c)
		{
			m_components.push_back(c);
			c->setEntity(this);
			return this;
		}

		std::vector<Component*> Entity::getComponents() const
		{
			return m_components;
		}
	}
}
