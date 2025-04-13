#include "PhysicsSystem.h"

inline void PhysicsSystem_Init(PhysicsSystem* system, int pageSize, int initCapacity) {
	system->rigidbodies = SPRigidbody_Init(pageSize, initCapacity);
	system->transforms = SPTransform_Init(pageSize, initCapacity);
}

inline void PhysicsSystem_Free(PhysicsSystem* system) {
	SPRigidbody_Free(&system->rigidbodies);
	SPTransform_Free(&system->transforms);
}

void PhysicsSystem_Load(PhysicsSystem* system) {
	// TO ADD
}

inline void PhysicsSystem_AddTransform(PhysicsSystem* system, Entity ID, Transform* t) {
	SPTransform_Insert(&system->transforms, t, ID);
}

inline void PhysicsSystem_AddRigidbody(PhysicsSystem* system, Entity ID, Rigidbody* t) {
	SPRigidbody_Insert(&system->rigidbodies, t, ID);
}

Transform* PhysicsSystem_GetTransform(PhysicsSystem* system, Entity ID) {
	if (&system->transforms.dense.data == NULL) {
		assert("PHYSICS SYSTEM TRANSFORM SET NOT INITIALIZED!");
		return NULL;
	}

	return SPTransform_Get(&system->transforms, ID);
};

Rigidbody* PhysicsSystem_GetRigidbody(PhysicsSystem* system, Entity ID) {
	if (&system->rigidbodies.dense.data == NULL) {
		assert("PHYSICS SYSTEM RIGIDBODY SET NOT INITIALIZED!");
		return NULL;
	}

	return SPRigidbody_Get(&system->rigidbodies, ID);
};

inline void PhysicsSystem_RemoveTransform(PhysicsSystem* system, Entity ID) {
	SPTransform_Remove(&system->transforms, ID);
}

inline void PhysicsSystem_RemoveRigidbody(PhysicsSystem* system, Entity ID) {
	SPRigidbody_Remove(&system->rigidbodies, ID);
}

inline void PhysicsSystem_RemoveAll(PhysicsSystem* system, Entity ID) {
	PhysicsSystem_RemoveTransform(system, ID);
	PhysicsSystem_RemoveRigidbody(system, ID);
}