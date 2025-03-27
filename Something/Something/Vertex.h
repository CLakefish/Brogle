#pragma once

#include "Math.h"
#include "DynamicArray.h"

#ifndef VERTEX
#define VERTEX

typedef struct Vertex {
	Vector3 position;
	Vector3 normal;
	float uvX;
	float uvY;
} Vertex;

GEN_DYNAMIC_ARRAY_TYPE(Vertex);
static inline int DAVertex_Equivalent(Vertex a, Vertex b) {
	return vec3_Equals(a.position, b.position) == 1;
}

#endif // !VERTEX