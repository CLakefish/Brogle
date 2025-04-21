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

	void ImGui_Render(unsigned int fboTex, unsigned int w, unsigned int h, int* outW, int* outH) {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// https://www.youtube.com/watch?v=wK2Qr8Yl6og
		ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

		// if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Begin("FBO Preview", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
		ImVec2 panelSize = ImGui::GetContentRegionAvail();

		ImGui::Image((ImTextureID)fboTex, ImVec2{ (float)w, (float)h }, ImVec2{0,1}, ImVec2{ 1, 0});

		*outW = (int)panelSize.x;
		*outH = (int)panelSize.y;

		ImGui::End();

		ImGui::Begin("Hello");
		ImGui::Text("Hello, World!");
		ImGui::End();

		ImGui::Begin("Hello2");
		ImGui::Text("Hello2, World!");
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