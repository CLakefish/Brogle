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

static struct ModelSystem {
	SPModel models;
	Shader* shader;
} ModelSystem;

static inline void ModelSystem_Init(int pageSize, int initCapacity) {
	ModelSystem.models = SPModel_Init(pageSize, initCapacity);
}

static inline void ModelSystem_Add(Entity ID, Model* model) {
	SPModel_Insert(&ModelSystem.models, model, ID);
}

static inline void ModelSystem_Render(Matrix4x4* view, Matrix4x4* proj) {
	ShaderUse(ModelSystem.shader);

	unsigned int viewLoc = glGetUniformLocation(ModelSystem.shader->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view);

	unsigned int projLoc = glGetUniformLocation(ModelSystem.shader->ID, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_TRUE, proj);

	for (int i = 0; i < ModelSystem.models.dense.count; ++i) {
		Model m = ModelSystem.models.dense.data[i];
		for (int j = 0; j < m.mesh.count; ++j) {
			Mesh_Render(&m.mesh.data[j], PhysicsSystem_GetTransform(m.ID), ModelSystem.shader);
		}
	}
}

static inline void ModelSystem_Free() {
	// Fix this?
	for (int i = 0; i < ModelSystem.models.dense.count; ++i) {
		int clearable = 1;

		for (int j = 0; j < ModelSystem.models.dense.data[i].mesh.count; ++j)
		{
			Mesh_Free(&ModelSystem.models.dense.data[i].mesh.data[j], &clearable);
		}

		if (clearable) {
			DAMesh_Free(&ModelSystem.models.dense.data[i].mesh);
		}
	}

	SPModel_Free(&ModelSystem.models);
	free(ModelSystem.shader);
}

#endif // !MODEL_SYSTEM
