#pragma once

#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>

#include "SparseSet.h"

#include "PhysicsSystem.h"

#include "Entity.h"
#include "Model.h"

#include "Shader.h"

#ifndef MODEL_SYSTEM
#define MODEL_SYSTEM

GEN_SPARSE_SET_TYPE(Model, int);

typedef struct ModelSystem {
	SPModel models;
	Shader* shader;

	unsigned int viewLoc;
	unsigned int projLoc;
} ModelSystem;

inline void ModelSystem_Init		(ModelSystem* system, int pageSize, int initCapacity, Shader* shader);
void		ModelSystem_Free		(ModelSystem* system);

void		ModelSystem_Load		(ModelSystem* system);

inline void ModelSystem_Add			(ModelSystem* system, Entity ID, Model* model);
inline void ModelSystem_Remove		(ModelSystem* system, Entity ID);

void		ModelSystem_Render		(ModelSystem* system, Matrix4x4* view, Matrix4x4* proj);

#endif // !MODEL_SYSTEM
