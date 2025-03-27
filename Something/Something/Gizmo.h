#pragma once

#include "Vector3.h"
#include "DynamicArray.h"
#include "DynamicArrayPtr.h"

#ifndef GIZMO
#define GIZMO

typedef struct GizmoVertex {
	Vector3 position;
	Vector3 color;
} GizmoVertex;

typedef struct Line {
	GizmoVertex points[2];
} Line;

typedef struct GizmoLine {
	Line line;
	GLuint VAO, VBO;
} GizmoLine;

typedef struct GizmoBox {
	GizmoVertex points[24];
	GLuint VAO, VBO;
} GizmoBox;

GEN_DYNAMIC_ARRAY_PTR_TYPE(GizmoLine);
GEN_DYNAMIC_ARRAY_PTR_TYPE(GizmoBox);

#endif // !GIZMO
