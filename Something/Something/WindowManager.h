#pragma once

#include "Window.h"

#ifndef WINDOW_MANAGER
#define WINDOW_MANAGER

typedef struct {
	Window_t* ptr;
	size_t size;
	size_t capacity;
} WindowManager_t;

extern WindowManager_t windowManager;

Window_t* WindowManagerAddWindow(const Vector3 pos, const Vector3 size, const char* name, const Window_t* ptr);
void WindowManagerRemoveWindow(const Window_t wind);
void WindowManagerClear(void);

#endif // !WINDOW_MANAGER