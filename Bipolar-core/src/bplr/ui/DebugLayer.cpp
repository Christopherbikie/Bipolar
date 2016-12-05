#include "DebugLayer.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include "../input/Mouse.h"
#include <iostream>

namespace bplr
{
	namespace ui
	{
		void DebugLayer::init(graphics::Window* window)
		{
			m_window = window;

			ImGui_ImplGlfwGL3_Init(window->getGLFWwindow(), true);
		}

		void DebugLayer::update(GLfloat delta)
		{
			if (m_visible)
			{
				ImGuiIO& io = ImGui::GetIO();

				ImGui_ImplGlfwGL3_NewFrame();

				ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
				ImGui::ShowTestWindow(&m_visible);
			}
		}

		void DebugLayer::render()
		{
			if (m_visible)
				ImGui::Render();
		}

		DebugLayer::~DebugLayer()
		{
			ImGui_ImplGlfwGL3_Shutdown();
		}
	}
}
