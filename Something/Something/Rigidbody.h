#pragma once

#include "DynamicArray.h"
#include "Vector3.h"

#ifndef RIGIDBODY
#define RIGIDBODY

typedef struct Rigidbody {
	Vector3 velocity;
	Vector3 angularVelocity;
	float mass;
	unsigned int ID;
} Rigidbody;

static inline Rigidbody Rigidbody_Init(unsigned int ID) {
	return (Rigidbody) { { 0, 0, 0 }, {0, 0, 0}, 1, ID };
}

GEN_DYNAMIC_ARRAY_TYPE(Rigidbody);
static inline int DARigidbody_Equivalent(Rigidbody a, Rigidbody b) {
	return vec3_Equals(a.velocity, b.velocity) == 1 && vec3_Equals(a.angularVelocity, b.angularVelocity) == 1 && a.mass == b.mass;
}

#endif //!RIGIDBODY