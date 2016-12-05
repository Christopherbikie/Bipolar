#pragma once

#include "../graphics/layers/Layer.h"

namespace bplr
{
	namespace ui
	{
		class DebugLayer : graphics::Layer
		{
		public:
			void init(graphics::Window* window) override;
			void update(GLfloat delta) override;
			void render() override;

			~DebugLayer();
		};
	}
}
