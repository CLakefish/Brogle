#include "ModelSystem.h"

void ModelSystem_Init(ModelSystem* system, int pageSize, int initCapacity, Shader* shader) {
	system->models = SPModel_Init(pageSize, initCapacity);
	system->shader = shader;

	system->viewLoc = glGetUniformLocation(system->shader->ID, "view");
	system->projLoc = glGetUniformLocation(system->shader->ID, "proj");
}

void ModelSystem_Free(ModelSystem* system) {
	// Fix this?
	for (int i = 0; i < system->models.dense.count; ++i) {
		int clearable = 1;

		for (int j = 0; j < system->models.dense.data[i].mesh.count; ++j)
		{
			Mesh_Free(&system->models.dense.data[i].mesh.data[j], &clearable);
		}

		if (clearable) {
			DAMesh_Free(&system->models.dense.data[i].mesh);
		}
	}

	SPModel_Free(&system->models);
	free(system->shader);
	free(system);
}

void ModelSystem_Load(ModelSystem* system) {

}

void ModelSystem_Add(ModelSystem* system, Entity ID, Model* model) {
	SPModel_Insert(&system->models, model, ID);
}

void ModelSystem_Remove(ModelSystem* system, Entity ID) {
	SPModel_Remove(&system->models, ID);
}

void ModelSystem_Render(ModelSystem* system, PhysicsSystem* phys, Matrix4x4* view, Matrix4x4* proj) {
	ShaderUse(system->shader);

	glUniformMatrix4fv(system->viewLoc, 1, GL_TRUE, view);
	glUniformMatrix4fv(system->projLoc, 1, GL_TRUE, proj);

	for (int i = 0; i < system->models.dense.count; ++i) {
		Model m = system->models.dense.data[i];
		for (int j = 0; j < m.mesh.count; ++j) {
			Transform* t = PhysicsSystem_GetTransform(phys, m.ID);
			if (t == NULL) continue;
			Mesh_Render(&m.mesh.data[j], t, system->shader);
		}
	}
}