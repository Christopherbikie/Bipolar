#pragma once

#include <string>

namespace bplr
{
	namespace entity
	{
		class Entity;

		class Component
		{
		public:
			virtual ~Component()
			{
			}

			void setEntity(Entity* entity) { m_entity = entity; }
			Entity* getEntity() const { return m_entity; }

			virtual std::string getType() = 0;

		protected:
			Entity* m_entity;
		};
	}
}
