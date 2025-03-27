#include "TimeManager.h"
#include <GLFW/glfw3.h>

TimeManager_t TimeManager = { 1.0f, 0, 0, 0, 0, 0 };

void TimeManagerCalculate(void) {
	float current = glfwGetTime();

	TimeManager.unscaledDeltaTime = (current - TimeManager.lastFrame);
	TimeManager.deltaTime = TimeManager.unscaledDeltaTime * TimeManager.timeScale;

	TimeManager.unscaledTime += TimeManager.unscaledDeltaTime;
	TimeManager.time += TimeManager.deltaTime;

	TimeManager.lastFrame = current;
}