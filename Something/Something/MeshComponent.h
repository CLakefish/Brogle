#pragma once

#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"
#include "Vertex.h"
#include "Transform.h"

#ifndef	MESH_COMPONENT
#define MESH_COMPONENT

typedef struct Mesh {
	DAVertex vertices;
	DAint indices;

	GLuint VAO, VBO, EBO;
	Texture texture;
	unsigned int refCount;
} Mesh;

GEN_DYNAMIC_ARRAY_TYPE(Mesh);

// Needs to be fixed
static inline int DAMesh_Equivalent(Mesh a, Mesh b) {
	return a.vertices.capacity == b.vertices.capacity && a.vertices.count == b.vertices.count;
}

static Mesh Mesh_Init     (int vertC, Vertex* vert, int indC, int* ind, Texture tex);
static void Mesh_Calculate(Mesh* mesh);
static void Mesh_Render   (const Mesh* mesh, const Transform* t, const Shader* shader);
static void Mesh_Free	  (Mesh* mesh, int* clearable);

static Mesh Mesh_Init(int vertC, Vertex* vert, int indC, int* ind, Texture tex) {
	Mesh mesh;
	mesh.texture  = tex;
	mesh.refCount = 1;

	DAVertex_Init(&mesh.vertices, vertC);
	DAint_Init(&mesh.indices, indC);
	mesh.vertices.count = vertC;
	mesh.indices.count = indC;

	for (int i = 0; i < vertC; ++i) {
		mesh.vertices.data[i] = vert[i];
	}

	for (int i = 0; i < indC; ++i) {
		mesh.indices.data[i] = ind[i];
	}

	Mesh_Calculate(&mesh);
	return mesh;
}

static void Mesh_Calculate(Mesh* mesh) {
	// Vertex array object
	glGenVertexArrays(1, &mesh->VAO);
	glBindVertexArray(mesh->VAO);

	// Vertex buffer object
	glGenBuffers(1, &mesh->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
	glBufferData(GL_ARRAY_BUFFER, mesh->vertices.count * sizeof(Vertex), mesh->vertices.data, GL_STATIC_DRAW);

	// Element buffer
	glGenBuffers(1, &mesh->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.count * sizeof(int), mesh->indices.data, GL_STATIC_DRAW);

	// position layout in pos 0, size of value, data type, normalize, val, stride,
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(0));
	glEnableVertexAttribArray(0);

	// Uv layout
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, uvX)));
	glEnableVertexAttribArray(1);
}


static void Mesh_Render(const Mesh* mesh, const Transform* t, const Shader* shader) {
	Texture_Bind(&mesh->texture);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);

	Matrix4x4 model = mat_Identity();
	model = mat_Scale(model, t->scale);
	model = mat_Rot(model, t->eulers);
	model = mat_Translate(model, t->position);

	unsigned int modelLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_TRUE, &model);

	glBindVertexArray(mesh->VAO);
	glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.count);
}

static void Mesh_Free(Mesh* mesh, int* clearable) {
	if (mesh == NULL) return;

	if (--mesh->refCount > 0) {
		*clearable = 0;
		return;
	}

	if (mesh->vertices.data != NULL) DAVertex_Free(&mesh->vertices);
	if (mesh->indices.data  != NULL) DAint_Free   (&mesh->indices);

	glDeleteVertexArrays(1, &mesh->VAO);
	glDeleteBuffers(1, &mesh->VBO);
	glDeleteBuffers(1, &mesh->EBO);
}

#endif // !MESH_COMPONENT