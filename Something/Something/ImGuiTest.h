#pragma once

#ifndef IMGUI_TEST_H
#define IMGUI_TEST_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef __cplusplus
extern "C" {
#endif

	void ImGui_LoadGUI(GLFWwindow* wind);
	void ImGui_Render(unsigned int fboTex, unsigned int w, unsigned int h);
	void ImGui_ClearGUI(void);

#ifdef __cplusplus
}
#endif

#endif
