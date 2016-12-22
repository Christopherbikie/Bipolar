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

		void Entity::update(GLfloat delta)
		{
			for (Component* component : m_components)
				component->update(delta);
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

		void Entity::destroy()
		{
			m_destroyed = true;
		}

		bool Entity::isDestroyed() const
		{
			return m_destroyed;
		}
	}
}
