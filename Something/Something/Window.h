#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Vector3.h"

#ifndef WINDOW
#define WINDOW

typedef void (*WindowFunction)(void);

typedef struct {
	Vector3 position;
	Vector3 scale;
	const char* name;

	GLFWwindow* window;

	WindowFunction onUpdate;
	WindowFunction onEnter;
	WindowFunction onExit;
} Window_t;

#define WINDOW_INIT(wind, shared)																	   \
	    wind.window = glfwCreateWindow((int)wind.scale.x, (int)wind.scale.y, wind.name, NULL, shared); \
		if (wind.window == NULL)																	   \
		{																							   \
			perror("Failed to create GLFW window");													   \
			glfwTerminate();																		   \
			return NULL;																			   \
		}																							   \

#endif // !WINDOW