#include "Entity.h"

#pragma once

#ifndef ENTITY_MANAGER
#define ENTITY_MANAGER

typedef struct EntityManager {
	DAEntity stack;
	Entity   next;
} EntityManager;

inline void Entity_Init		(EntityManager* manager);
inline void Entity_Free		(EntityManager* manager);

void		Entity_Load		(EntityManager* manager);

Entity		Entity_Create	(EntityManager* manager);
inline void Entity_Destroy	(EntityManager* manager, Entity entity);

#endif // !ENTITY_MANAGER

