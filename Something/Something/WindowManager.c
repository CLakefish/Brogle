#include "WindowManager.h"
#include <stdlib.h>

WindowManager_t windowManager = { 0, 0, 1 };

Window_t* WindowManagerAddWindow(const Vector3 pos, const Vector3 size, const char* name, const Window_t* ptr)
{
	if (!windowManager.ptr)
	{
		windowManager.capacity = 2;
		windowManager.ptr = (Window_t*)malloc(sizeof(Window_t) * windowManager.capacity);

		if (!windowManager.ptr)
		{
			perror("Unable to allocate windowmanager ptr");
			return NULL;
		}
	}

	if (windowManager.size >= windowManager.capacity)
	{
		windowManager.capacity *= 2;

		Window_t* t = (Window_t*)realloc(windowManager.ptr, windowManager.capacity * sizeof(Window_t));

		if (t == NULL)
		{
			perror("Unable to expand windowmanager ptr");
			return NULL;
		}

		windowManager.ptr = t;
	}

	Window_t* wind = &windowManager.ptr[windowManager.size];
	*wind = (Window_t){
		.position = pos,
		.scale = size,
		.name = name,
	};

	if (ptr != NULL) {
		WINDOW_INIT((*wind), ptr->window);
	}
	else {
		WINDOW_INIT((*wind), NULL);
	}

	windowManager.size++;

	return wind;
}

void WindowManagerRemoveWindow(const Window_t wind)
{
	for (size_t i = 0; i < windowManager.size; ++i)
	{
		if (wind.name == windowManager.ptr[i].name)
		{
			for (size_t j = i; j < windowManager.size - 1; ++j)
			{
				windowManager.ptr[j] = windowManager.ptr[j + 1];
			}

			windowManager.size--;
			return;
		}
	}
}

void WindowManagerClear(void)
{
	free(windowManager.ptr);
	windowManager.ptr = NULL;
	windowManager.capacity = 0;
	windowManager.size = 0;
}