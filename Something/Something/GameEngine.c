#include "GameEngine.h"
#include "WindowManager.h"
#include "TimeManager.h"

void Engine_Init(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// _CrtMemCheckpoint(&GameEngine.old);

	// glfwSetFramebufferSizeCallback(main->window, callback);
	// glfwSetCursorPosCallback(main->window, mouse_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		perror("Failed to initialize GLAD");
		return -1;
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Engine_Free(void) {
	PhysicsSystem_Free(Engine.physics);
	ModelSystem_Free(Engine.render);
	Entity_Free(Engine.entity);
	// Gizmo_Free();

	WindowManagerClear();
	glfwTerminate();
}

void Engine_Run(void) {

	Window_t* main = WindowManagerAddWindow((Vector3) { 100, 100, 0, 1 }, (Vector3) { 1280, 720, 0, 1 }, "Main", NULL);
	Matrix4x4 proj = mat_Perspective(90.0f * DEG2RAD, 1.77777778f, 0.1f, 1000);

	glfwSetWindowAspectRatio(main->window, 16, 9);
	glfwMakeContextCurrent(main->window);
	glfwSetInputMode(main->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	while (!glfwWindowShouldClose(main->window))
	{
		TimeManagerCalculate();
		// processInput(main->window);

		glClearColor(0.1f, 0, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Matrix4x4 view = mat_LookAt(cam.pos, cam.forward, cam.right, cam.up);

		//Transform* t = PhysicsSystem_GetTransform(e4);
		//t->eulers   = (Vector3){ 0, TimeManager.time, 0 };
		//t->position = (Vector3){ 10, sinf(TimeManager.time), sinf(TimeManager.time) * 5 };

		ModelSystem_Render(Engine.render, &view, &proj);
		Gizmo_RenderTop(&view, &proj, cam.pos);

		glfwSwapBuffers(main->window);
		glfwPollEvents();
	}
}

void Engine_Update(void) {

}

void Engine_Render(void) {

}
