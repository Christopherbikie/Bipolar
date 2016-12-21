#pragma once
#include "Component.h"
#include "../../math/vec3.h"
#include "../../graphics/Shader.h"

namespace bplr
{
	namespace scene
	{
		class LightSourceComponent : public Component
		{
		public:
			LightSourceComponent(math::vec3 colour = math::vec3(1.0f), math::vec3 ambient = math::vec3(1.0f));

			math::vec3 getColour() const;
			void setColour(const math::vec3& colour);

			math::vec3 getAmbient() const;
			void setAmbient(const math::vec3& ambient);

			void loadUniforms(graphics::Shader* shader) const;

			std::string getType() override;
			static std::string getStaticType();

		private:
			math::vec3 m_colour, m_ambient;
		};
	}
}
