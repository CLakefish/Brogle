#pragma once

#include "SparseSet.h"
#include "Entity.h"

#include "Transform.h"
#include "Rigidbody.h"

#ifndef PHYSICS_SYSTEM
#define PHYSICS_SYSTEM

GEN_SPARSE_SET_TYPE(Transform, int);
GEN_SPARSE_SET_TYPE(Rigidbody, int);

static struct PhysicsSystem {
	SPRigidbody rigidbodies;
	SPTransform transforms;
} PhysicsSystem;

static void PhysicsSystem_Init(int pageSize, int initCapacity) {
	PhysicsSystem.rigidbodies = SPRigidbody_Init(pageSize, initCapacity);
	PhysicsSystem.transforms  = SPTransform_Init(pageSize, initCapacity);
}

static inline void PhysicsSystem_Load() {
	// TO ADD
}

static inline void PhysicsSystem_Free() {
	SPRigidbody_Free(&PhysicsSystem.rigidbodies);
	SPTransform_Free(&PhysicsSystem.transforms);
}

static inline void PhysicsSystem_AddTransform(Entity ID, Transform* t) {
	SPTransform_Insert(&PhysicsSystem.transforms, t, ID);
}

static inline void PhysicsSystem_AddRigidbody(Entity ID, Rigidbody* t) {
	SPRigidbody_Insert(&PhysicsSystem.rigidbodies, t, ID);
}

static inline Transform* PhysicsSystem_GetTransform(Entity ID) {
	if (PhysicsSystem.transforms.dense.data == NULL) {
		assert("PHYSICS SYSTEM TRANSFORM SET NOT INITIALIZED!");
		return NULL;
	}

	return SPTransform_Get(&PhysicsSystem.transforms, ID);
};

static inline Rigidbody* PhysicsSystem_GetRigidbody(Entity ID) {
	if (PhysicsSystem.rigidbodies.dense.data == NULL) {
		assert("PHYSICS SYSTEM RIGIDBODY SET NOT INITIALIZED!");
		return NULL;
	}

	return SPRigidbody_Get(&PhysicsSystem.rigidbodies, ID);
};

static inline void PhysicsSystem_RemoveTransform(Entity ID) {
	SPTransform_Remove(&PhysicsSystem.transforms, ID);
}

static inline void PhysicsSystem_RemoveRigidbody(Entity ID) {
	SPRigidbody_Remove(&PhysicsSystem.rigidbodies, ID);
}

static inline void PhysicsSystem_RemoveAll(Entity ID) {
	PhysicsSystem_RemoveTransform(ID);
	PhysicsSystem_RemoveRigidbody(ID);
}

#endif // !PHYSICS_SYSTEM
