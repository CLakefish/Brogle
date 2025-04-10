#pragma once

#include "SparseSet.h"
#include "Entity.h"

#include "Transform.h"
#include "Rigidbody.h"

#ifndef PHYSICS_SYSTEM
#define PHYSICS_SYSTEM

GEN_SPARSE_SET_TYPE(Transform, int);
GEN_SPARSE_SET_TYPE(Rigidbody, int);

typedef struct PhysicsSystem {
	SPRigidbody rigidbodies;
	SPTransform transforms;
} PhysicsSystem;

inline void PhysicsSystem_Init				(PhysicsSystem* system, int pageSize, int initCapacity);
inline void PhysicsSystem_Free				(PhysicsSystem* system);

void		PhysicsSystem_Load				(PhysicsSystem* system);

inline void PhysicsSystem_AddTransform		(PhysicsSystem* system, Entity ID, Transform* t);
inline void PhysicsSystem_AddRigidbody		(PhysicsSystem* system, Entity ID, Rigidbody* t);

Transform*	PhysicsSystem_GetTransform		(PhysicsSystem* system, Entity ID);
Rigidbody*	PhysicsSystem_GetRigidbody		(PhysicsSystem* system, Entity ID);

inline void PhysicsSystem_RemoveTransform	(PhysicsSystem* system, Entity ID);
inline void PhysicsSystem_RemoveRigidbody	(PhysicsSystem* system, Entity ID);
inline void PhysicsSystem_RemoveAll			(PhysicsSystem* system, Entity ID);

#endif // !PHYSICS_SYSTEM
