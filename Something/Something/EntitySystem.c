#include "EntitySystem.h"

void EntitySystem_Init(EntitySystem* manager) {
	DAEntity_Init(&manager->stack, 2);
	manager->next = 0;
}

void EntitySystem_Free(EntitySystem* manager) {
	DAEntity_Free(&manager->stack);
	manager->next = 0;
	free(manager);
}

void EntitySystem_Load(EntitySystem* manager) {
	// TO ADD
}

Entity EntitySystem_Create(EntitySystem* manager) {
	if (manager->stack.count > 0) {
		Entity entity = manager->stack.data[manager->stack.count - 1];
		manager->stack.count--;
		return entity;
	}

	return manager->next++;
}

void EntitySystem_Destroy(EntitySystem* manager, Entity entity) {
	DAEntity_Push(&manager->stack, &entity);
}