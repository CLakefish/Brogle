#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>  
#include <crtdbg.h>

#include "PhysicsSystem.h"
#include "ModelSystem.h"
#include "EntityManager.h"

#ifndef GAME_ENGINE
#define GAME_ENGINE

static struct GameEngine {
	EntityManager* entity;
	PhysicsSystem* physics;
	ModelSystem*   render;

	int debugMode;
} Engine;

void Engine_Init(void);
void Engine_Free(void);

void Engine_Run(void);

void Engine_Update(void);
void Engine_Render(void);

#endif
