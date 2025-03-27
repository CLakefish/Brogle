#pragma once

#ifndef IMGUI_MANAGER
#define IMGUI_MANAGER

#include <glad/glad.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

static void ImGUI_Init(GLFWwindow* window);

#endif // !IMGUI_MANAGER