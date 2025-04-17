#include "ImGuiTest.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

extern "C" {
	bool show_demo_window = true;

	void ImGui_LoadGUI(GLFWwindow* wind)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui_ImplGlfw_InitForOpenGL(wind, true);
		ImGui_ImplOpenGL3_Init();
	}

	void ImGui_Render(unsigned int fboTex, unsigned int w, unsigned int h) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// https://www.youtube.com/watch?v=wK2Qr8Yl6og
		ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

		// if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Begin("FBO Preview");
		ImVec2 panelSize = ImGui::GetContentRegionAvail();
		ImGui::End();
		
		if ()

		ImGui::Begin("Hello");

		ImGui::Text("Hello, World!");

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGui_ClearGUI(void) {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}