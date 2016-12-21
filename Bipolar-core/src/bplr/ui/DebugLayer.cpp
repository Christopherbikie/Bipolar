#include "../graphics/Shader.h"
#include "DebugLayer.h"
#include "../input/Keyboard.h"
#include "imgui/imgui_impl_glfw_gl3.h"

namespace bplr
{
	namespace ui
	{
		void DebugLayer::init(graphics::Window* window)
		{
			m_window = window;

			ImGui_ImplGlfwGL3_Init(window->getGLFWwindow(), false);
			glfwSetCharCallback(m_window->getGLFWwindow(), ImGui_ImplGlfwGL3_CharCallback);
			glfwSetScrollCallback(window->getGLFWwindow(), ImGui_ImplGlfwGL3_ScrollCallback);
		}

		void DebugLayer::updateInputCapture()
		{
			ImGuiIO& io = ImGui::GetIO();
			if (io.WantCaptureKeyboard && m_currentCallback == Bipolar) {
				glfwSetKeyCallback(m_window->getGLFWwindow(), ImGui_ImplGlfwGL3_KeyCallback);
				input::Keyboard::releaseAllKeys();
				m_currentCallback = ImGui;
			}
			else if (!io.WantCaptureKeyboard && m_currentCallback == ImGui)
			{
				glfwSetKeyCallback(m_window->getGLFWwindow(), input::Keyboard::keyCallback);
				m_currentCallback = Bipolar;
			}
		}

		void DebugLayer::update(GLfloat delta)
		{
			if (m_visible)
			{
				ImGui_ImplGlfwGL3_NewFrame();

				GLfloat framerate = ImGui::GetIO().Framerate;

				ImGui::Begin("Debug Menu", &m_visible);
				ImGui::Text("Application average: %.3f ms/frame (%.1f FPS)", 1000.0f / framerate, framerate);
				if (ImGui::Button("Reload shaders"))
					graphics::reloadShaders();
				ImGui::End();
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
