#pragma once

#include "DynamicArray.h"

#ifndef ENTITY
#define ENTITY

typedef unsigned int Entity;

GEN_DYNAMIC_ARRAY_TYPE(Entity);
int DAEntity_Equivalent(Entity a, Entity b) {
	return a == b ? 1 : 0;
}

#endif // !ENTITY