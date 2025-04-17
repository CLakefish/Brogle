#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>  
#include <crtdbg.h>

#include "PhysicsSystem.h"
#include "ModelSystem.h"
#include "EntitySystem.h"
#include "GizmoManager.h"

#include "Camera.h"
#include "Window.h"

#ifndef GAME_ENGINE
#define GAME_ENGINE

static struct GameEngine {
	EntitySystem* entity;
	PhysicsSystem* physics;
	ModelSystem*   render;

	Camera_t cam;
	Window_t* window;

	_CrtMemState sOld;
	_CrtMemState sNew;
	_CrtMemState sDiff;

	int debugMode;
} Engine;

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Camera_t* cam);

void Engine_Init(void);
void Engine_Free(void);

void Engine_Run(void);

#endif
