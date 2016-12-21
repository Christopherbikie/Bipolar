#pragma once

#include <string>

namespace bplr
{
	namespace scene
	{
		class Entity;

		class Component
		{
		public:
			virtual ~Component()
			{
			}

			virtual void setEntity(Entity* entity) { m_entity = entity; }
			Entity* getEntity() const { return m_entity; }

			virtual std::string getType() = 0;

		protected:
			Entity* m_entity;
		};
	}
}
