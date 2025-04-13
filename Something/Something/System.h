#pragma once

#include <stdbool.h>

#ifndef SYSTEM
#define SYSTEM

typedef void (*SystemFunction)(void);

typedef struct System {
	const char* name;
	unsigned int ID;
	bool simulate;
	SystemFunction onEnter;
	SystemFunction onUpdate;
	SystemFunction onRender;
	SystemFunction onExit;
} System_t;

#endif // !SYSTEM
