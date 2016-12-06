#pragma once

#include "../graphics/layers/Layer.h"

namespace bplr
{
	namespace ui
	{
		enum KeyCallbackState
		{
			Bipolar,
			ImGui,
		};

		class DebugLayer : graphics::Layer
		{
		public:
			void init(graphics::Window* window) override;
			void updateInputCapture();
			void update(GLfloat delta) override;
			void render() override;

			~DebugLayer();

		private:
			KeyCallbackState m_currentCallback = Bipolar;
		};
	}
}
