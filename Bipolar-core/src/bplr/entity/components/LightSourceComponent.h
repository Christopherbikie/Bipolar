#pragma once
#include "Component.h"
#include "../../math/vec3.h"

namespace bplr
{
	namespace entity
	{
		class LightSourceComponent : public Component
		{
		public:
			LightSourceComponent(math::vec3 colour = math::vec3(1.0f));

			math::vec3 getColour() const;
			void setColour(math::vec3 colour);

			std::string getType() override;
			static std::string getStaticType();

		private:
			math::vec3 m_colour;
		};
	}
}
