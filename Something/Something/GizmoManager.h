#pragma once

#include "Shader.h"
#include "Gizmo.h"
#include "Vector3.h"

#include <glad/glad.h>
#include <assert.h>

#ifndef GIZMO_MANAGER
#define GIZMO_MANAGER

#define GRID_WIDTH		 75
#define GRID_LENGTH		 75
#define GRID_SPACING	 15.0f
#define GRID_FOG_DROPOFF 400.0f

typedef enum GizmoType {
	GT_WORLD,
	GT_OVERLAY,
	GT_SCREEN,
} GizmoType;

static struct GizmoManager {
	DAPGizmoBox  boxes;
	DAPGizmoLine worldLines;
	DAPGizmoLine overlayLines;
	DAPGizmoLine screenLines;

	GLuint gridVBO, gridVAO;
	GizmoVertex* gridVert;
	int gridInd;

	Shader* shader;
	unsigned int viewLoc;
	unsigned int projLoc;
} GizmoManager;

static void Gizmo_Init(Shader* shader) {
	DAPGizmoBox_Init(&GizmoManager.boxes, 2);
	DAPGizmoLine_Init(&GizmoManager.worldLines, 2);
	DAPGizmoLine_Init(&GizmoManager.overlayLines, 2);
	DAPGizmoLine_Init(&GizmoManager.screenLines, 2);

	GizmoManager.shader = shader;
	GizmoManager.viewLoc = glGetUniformLocation(GizmoManager.shader->ID, "view");
	GizmoManager.projLoc = glGetUniformLocation(GizmoManager.shader->ID, "proj");

	int cell = GRID_WIDTH * GRID_LENGTH;
	int inds = cell * 4;

	GizmoManager.gridInd = inds;
	GizmoManager.gridVert = (GizmoVertex*)malloc(sizeof(GizmoVertex) * GizmoManager.gridInd);

	glGenVertexArrays(1, &GizmoManager.gridVAO);
	glBindVertexArray(GizmoManager.gridVAO);
	glGenBuffers(1, &GizmoManager.gridVBO);
	glBindBuffer(GL_ARRAY_BUFFER, GizmoManager.gridVBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), (void*)offsetof(GizmoVertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), (void*)offsetof(GizmoVertex, color));
	glEnableVertexAttribArray(1);
}

static GizmoLine* Gizmo_GenGizmoLine(Vector3 a, Vector3 b, Vector3 color) {
	GizmoLine* gizmo = (GizmoLine*)malloc(sizeof(GizmoLine));
	if (!gizmo) {
		assert("UNABLE TO ALLOCATE GIZMO ON HEAP!");
		return NULL;
	}

	color.w = 1;
	*gizmo = (GizmoLine){ (Line) { { {a ,color}, {b,color}} } };

	glGenVertexArrays(1, &gizmo->VAO);
	glBindVertexArray(gizmo->VAO);

	glGenBuffers(1, &gizmo->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, gizmo->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GizmoLine), gizmo, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), (void*)offsetof(GizmoVertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), (void*)offsetof(GizmoVertex, color));
	glEnableVertexAttribArray(1);

	return gizmo;
}

static void Gizmo_Free() {
	DAPGizmoBox_Free(&GizmoManager.boxes);
	DAPGizmoLine_Free(&GizmoManager.worldLines);
	DAPGizmoLine_Free(&GizmoManager.overlayLines);
	DAPGizmoLine_Free(&GizmoManager.screenLines);

	free(GizmoManager.gridVert);

	ShaderClear(GizmoManager.shader);
}

static GizmoLine* Gizmo_AddLine(Vector3 a, Vector3 b, Vector3 color, GizmoType type) {
	GizmoLine* line = Gizmo_GenGizmoLine(a, b, color);
	
	switch (type)
	{
		case GT_WORLD:
			DAPGizmoLine_Push(&GizmoManager.worldLines, line);
			break;

		case GT_OVERLAY:
			DAPGizmoLine_Push(&GizmoManager.overlayLines, line);
			break;

		case GT_SCREEN:
			DAPGizmoLine_Push(&GizmoManager.screenLines, line);
			break;
	}

	return line;
}

static GizmoBox* Gizmo_AddBox(Vector3 position, Vector3 scale, Vector3 color) {
	// IMPROVE THIS!
	GizmoBox* box = (GizmoBox*)malloc(sizeof(GizmoBox));
	if (!box) {
		return NULL;
	}

	color.w = 1;
	Vector3 halfSize = vec3_Divide(scale, 2.0f);

	box->points[0] = (GizmoVertex){
		vec3_Add(position, (Vector3) { halfSize.x, halfSize.y, halfSize.z }),
		color
	};
	box->points[1] = (GizmoVertex){
		vec3_Add(position, (Vector3) { -halfSize.x, halfSize.y, halfSize.z }),
		color
	};
	// Line 1: left front vertical (top to bottom)
	box->points[2] = (GizmoVertex){
		box->points[1].position,
		color
	};
	box->points[3] = (GizmoVertex){
		vec3_Add(position, (Vector3) { -halfSize.x, -halfSize.y, halfSize.z }),
		color
	};
	// Line 2: bottom front edge
	box->points[4] = (GizmoVertex){
		box->points[3].position,
		color
	};
	box->points[5] = (GizmoVertex){
		vec3_Add(position, (Vector3) { halfSize.x, -halfSize.y, halfSize.z }),
		color
	};
	// Line 3: right front vertical (bottom to top)
	box->points[6] = (GizmoVertex){
		box->points[5].position,
		color
	};
	box->points[7] = (GizmoVertex){
		box->points[0].position,
		color
	};
	// Line 4: left side, front-to-back from bottom left front
	box->points[8] = (GizmoVertex){
		box->points[3].position,
		color
	};
	box->points[9] = (GizmoVertex){
		vec3_Add(box->points[3].position, (Vector3) { 0, 0, -scale.z }),
		color
	};
	// Line 5: right side, front-to-back from bottom right front
	box->points[10] = (GizmoVertex){
		box->points[5].position,
		color
	};
	box->points[11] = (GizmoVertex){
		vec3_Add(box->points[5].position, (Vector3) { 0, 0, -scale.z }),
		color
	};
	// Line 6: left back vertical (upwards)
	box->points[12] = (GizmoVertex){
		box->points[9].position,
		color
	};
	box->points[13] = (GizmoVertex){
		vec3_Add(box->points[9].position, (Vector3) { 0, scale.y, 0 }),
		color
	};
	// Line 7: right back vertical (upwards)
	box->points[14] = (GizmoVertex){
		box->points[11].position,
		color
	};
	box->points[15] = (GizmoVertex){
		vec3_Add(box->points[11].position, (Vector3) { 0, scale.y, 0 }),
		color
	};
	// Line 8: back bottom edge
	box->points[16] = (GizmoVertex){
		box->points[12].position,
		color
	};
	box->points[17] = (GizmoVertex){
		box->points[14].position,
		color
	};
	// Line 9: back top edge
	box->points[18] = (GizmoVertex){
		box->points[13].position,
		color
	};
	box->points[19] = (GizmoVertex){
		box->points[15].position,
		color
	};
	// Line 10: left side back-to-front vertical (left back)
	box->points[20] = (GizmoVertex){
		box->points[13].position,
		color
	};
	box->points[21] = (GizmoVertex){
		box->points[1].position,
		color
	};
	// Line 11: right side back-to-front vertical (right back)
	box->points[22] = (GizmoVertex){
		box->points[15].position,
		color
	};
	box->points[23] = (GizmoVertex){
		box->points[0].position,
		color
	};

	glGenVertexArrays(1, &box->VAO);
	glBindVertexArray(box->VAO);

	glGenBuffers(1, &box->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, box->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GizmoVertex) * 24, box->points, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), (void*)offsetof(GizmoVertex, position));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), (void*)offsetof(GizmoVertex, color));
	glEnableVertexAttribArray(1);

	DAPGizmoBox_Push(&GizmoManager.boxes, box);
	return box;
}

static void Gizmo_BuildGrid(Vector3 pos) {
	float xOffset = (int)(pos.x / GRID_SPACING) * GRID_SPACING;
	float zOffset = (int)(pos.z / GRID_SPACING) * GRID_SPACING;

	int halfWidth = GRID_WIDTH / 2.0f;
	int halfLength = GRID_LENGTH / 2.0f;

	Vector3 aZ, bZ, aX, bX;
	int index = 0;
	pos.y = 0;

	for (int x = -halfWidth; x < halfWidth; ++x) {
		for (int z = -halfLength; z < halfLength; ++z) {
			aZ = (Vector3){ (x * GRID_SPACING) - xOffset, 0, (z * GRID_SPACING) - zOffset };
			bZ = (Vector3){ (x * GRID_SPACING) - xOffset, 0, ((z + 1) * GRID_SPACING) - zOffset };

			Vector3 colorA = (Vector3){ 0.5f, 0.5f, 0.5f, 1.0f - (vec3_Distance(vec3_Multiply(pos, -1), aZ) / GRID_FOG_DROPOFF) };
			Vector3 colorB = (Vector3){ 0.5f, 0.5f, 0.5f, 1.0f - (vec3_Distance(vec3_Multiply(pos, -1), aZ) / GRID_FOG_DROPOFF) };

			GizmoManager.gridVert[index++] = (GizmoVertex){ aZ, colorA };
			GizmoManager.gridVert[index++] = (GizmoVertex){ bZ, colorB };

			aX = (Vector3){ (x * GRID_SPACING) - xOffset,	    0, (z * GRID_SPACING) - zOffset };
			bX = (Vector3){ ((x + 1) * GRID_SPACING) - xOffset, 0, (z * GRID_SPACING) - zOffset };

			GizmoManager.gridVert[index++] = (GizmoVertex){ aX, colorA };
			GizmoManager.gridVert[index++] = (GizmoVertex){ bX, colorB };
		}
	}

	aZ = (Vector3){ ( halfWidth * GRID_SPACING) - xOffset, 0, (halfLength * GRID_SPACING) - zOffset };
	bZ = (Vector3){ (-halfWidth * GRID_SPACING) - xOffset, 0, (halfLength * GRID_SPACING) - zOffset };

	Vector3 colorA = (Vector3){ 0.5f, 0.5f, 0.5f, 1.0f - (vec3_Distance(vec3_Multiply(pos, -1), aZ) / GRID_FOG_DROPOFF) };
	Vector3 colorB = (Vector3){ 0.5f, 0.5f, 0.5f, 1.0f - (vec3_Distance(vec3_Multiply(pos, -1), aZ) / GRID_FOG_DROPOFF) };

	GizmoManager.gridVert[index++] = (GizmoVertex){ aZ, colorA };
	GizmoManager.gridVert[index++] = (GizmoVertex){ bZ, colorB };

	aX = (Vector3){ (halfWidth * GRID_SPACING) - xOffset, 0, (-halfLength * GRID_SPACING) - zOffset };
	bX = (Vector3){ (halfWidth * GRID_SPACING) - xOffset, 0, (halfLength * GRID_SPACING) - zOffset };

	GizmoManager.gridVert[index++] = (GizmoVertex){ aX, colorA };
	GizmoManager.gridVert[index++] = (GizmoVertex){ bX, colorB };
}

static void Gizmo_Render(Matrix4x4* view, Matrix4x4* proj, Vector3 pos) {
	ShaderUse(GizmoManager.shader);

	glUniformMatrix4fv(GizmoManager.viewLoc, 1, GL_TRUE, view);
	glUniformMatrix4fv(GizmoManager.projLoc, 1, GL_TRUE, proj);

	// Grid Rendering
	Gizmo_BuildGrid((Vector3) {-pos.x, pos.y, -pos.z});

	glBindBuffer(GL_ARRAY_BUFFER, GizmoManager.gridVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GizmoVertex) * GizmoManager.gridInd, GizmoManager.gridVert, GL_DYNAMIC_DRAW);
	glBindVertexArray(GizmoManager.gridVAO);
	glDrawArrays(GL_LINES, 0, GizmoManager.gridInd);

	// Box Rendering
	for (int i = 0; i < GizmoManager.boxes.count; ++i)
	{
		glBindVertexArray(GizmoManager.boxes.data[i]->VAO);
		glDrawArrays(GL_LINES, 0, 24);
	}

	for (int i = 0; i < GizmoManager.worldLines.count; ++i)
	{
		glBindVertexArray(GizmoManager.worldLines.data[i]->VAO);
		glDrawArrays(GL_LINES, 0, 2);
	}

	// Line Rendering
	glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < GizmoManager.overlayLines.count; ++i)
	{
		glBindVertexArray(GizmoManager.overlayLines.data[i]->VAO);
		glDrawArrays(GL_LINES, 0, 2);
	}

	Matrix4x4 id = mat_Identity();
	glUniformMatrix4fv(GizmoManager.viewLoc, 1, GL_TRUE, &id);
	glUniformMatrix4fv(GizmoManager.projLoc, 1, GL_TRUE, &id);

	for (int i = 0; i < GizmoManager.screenLines.count; ++i)
	{
		glBindBuffer(GL_ARRAY_BUFFER, GizmoManager.screenLines.data[i]->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GizmoLine), GizmoManager.screenLines.data[i]);

		glBindVertexArray(GizmoManager.screenLines.data[i]->VAO);
		glDrawArrays(GL_LINES, 0, 2);
	}

	glEnable(GL_DEPTH_TEST);
}

#endif // !GIZMO_MANAGER
