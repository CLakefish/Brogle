#pragma once

#include "DynamicArray.h"
#include "Vector3.h"

#ifndef TRANSFORM
#define TRANSFORM

typedef struct Transform {
	Vector3 position;
	Vector3 eulers;
	Vector3 scale;
	unsigned int ID;
} Transform;

static inline Transform Transform_Init(unsigned int ID) {
	return (Transform) { { 0, 0, 0 }, {0, 0, 0}, {1, 1, 1}, ID };
}

GEN_DYNAMIC_ARRAY_TYPE(Transform);
static inline int DATransform_Equivalent(Transform a, Transform b) {
	return vec3_Equals(a.position, b.position) == 1 && vec3_Equals(a.eulers, b.eulers) == 1 && vec3_Equals(a.scale, b.scale) == 1;
};

#endif // !TRANSFORM
