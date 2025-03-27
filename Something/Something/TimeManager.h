#pragma once

#ifndef TIME_MANAGER
#define TIME_MANAGER

typedef struct {
	float timeScale;

	float time;
	float deltaTime;
	float unscaledTime;
	float unscaledDeltaTime;

	float lastFrame;
} TimeManager_t;

extern TimeManager_t TimeManager;

void TimeManagerCalculate(void);

#endif