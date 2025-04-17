#include "Entity.h"

#pragma once

#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

typedef struct EntitySystem {
	DAEntity stack;
	Entity   next;
} EntitySystem;

void	EntitySystem_Init		(EntitySystem* manager);
void	EntitySystem_Free		(EntitySystem* manager);

void	EntitySystem_Load		(EntitySystem* manager);

Entity	EntitySystem_Create		(EntitySystem* manager);
void	EntitySystem_Destroy	(EntitySystem* manager, Entity entity);

#endif // !ENTITY_MANAGER

