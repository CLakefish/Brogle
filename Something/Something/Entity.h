#pragma once

#include "DynamicArray.h"

#ifndef ENTITY
#define ENTITY

typedef unsigned int Entity;

GEN_DYNAMIC_ARRAY_TYPE(Entity);
int DAEntity_Equivalent(Entity a, Entity b) {
	return a == b ? 1 : 0;
}

static struct EntityManager {
	DAEntity stack;
	Entity   next;
} EntityManager;

static inline void EntityManager_Init() {
	DAEntity_Init(&EntityManager.stack, 2);
	EntityManager.next = 0;
}

static inline void EntityManager_Free() {
	DAEntity_Free(&EntityManager.stack);
	EntityManager.next = 0;
}

static Entity EntityManager_InstantiateEntity() {
	if (EntityManager.stack.count > 0) {
		Entity entity = EntityManager.stack.data[EntityManager.stack.count - 1];
		EntityManager.stack.count--;
		return entity;
	}

	return EntityManager.next++;
}

static inline void EntityManager_DestroyEntity(Entity entity) {
	DAEntity_Push(&EntityManager.stack, &entity);
}

#endif // !ENTITY