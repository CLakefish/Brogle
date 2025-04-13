#include "EntityManager.h"

inline void Entity_Init(EntityManager* manager) {
	DAEntity_Init(&manager->stack, 2);
	manager->next = 0;
}

inline void Entity_Free(EntityManager* manager) {
	DAEntity_Free(&manager->stack);
	manager->next = 0;
}

void Entity_Load(EntityManager* manager) {
	// TO ADD
}

Entity Entity_Create(EntityManager* manager) {
	if (manager->stack.count > 0) {
		Entity entity = manager->stack.data[manager->stack.count - 1];
		manager->stack.count--;
		return entity;
	}

	return manager->next++;
}

inline void Entity_Destroy(EntityManager* manager, Entity entity) {
	DAEntity_Push(&manager->stack, &entity);
}