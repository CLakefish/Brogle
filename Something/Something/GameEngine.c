#include "GameEngine.h"
#include "WindowManager.h"
#include "TimeManager.h"

#include "ImGuiTest.h"

#include "FileIO.h"

unsigned int tex;
bool firstMouse = true;
double lastX = 0, lastY = 0;
float moveSpeed = 10;
float pitch, yaw = -90.0f;

unsigned int texW = 1920, texH = 1080;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = lastX - xpos;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	CLAMP(pitch, -89.9f, 89.9f);

	Vector3 dir = {0,0,0};
	dir.x = cosf(yaw   * DEG2RAD) * cosf(pitch * DEG2RAD);
	dir.y = sinf(pitch * DEG2RAD);
	dir.z = sinf(yaw   * DEG2RAD) * cosf(pitch * DEG2RAD);
	Engine.cam.forward = vec3_Normalize(dir);
	Engine.cam.right   = vec3_Normalize(vec3_Cross(Engine.cam.forward, (Vector3) { 0, 1, 0 }));
	Engine.cam.up	   = vec3_Normalize(vec3_Cross(Engine.cam.right, Engine.cam.forward));
}
void callback	   (GLFWwindow* window, int width, int height)
{
	Engine.window->scale = (Vector3){ width, height, 0 };
	glViewport(0, 0, width, height);
}
void processInput  (GLFWwindow* window, Camera_t* cam)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetInputMode(window, GLFW_CURSOR, glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
		firstMouse = true;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		cam->pos = vec3_Add(cam->pos, vec3_Multiply((Vector3) { 0, 1, 0 }, moveSpeed* TimeManager.deltaTime));
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		cam->pos = vec3_Subtract(cam->pos, vec3_Multiply((Vector3) { 0, 1, 0 }, moveSpeed* TimeManager.deltaTime));
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cam->pos = vec3_Subtract(cam->pos, vec3_Multiply(cam->forward, moveSpeed * TimeManager.deltaTime));
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cam->pos = vec3_Add(cam->pos, vec3_Multiply(cam->forward, moveSpeed * TimeManager.deltaTime));
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Vector3 dir = vec3_Multiply(vec3_Normalize(vec3_Cross(cam->forward, cam->up)), moveSpeed * TimeManager.deltaTime);
		cam->pos = vec3_Subtract(cam->pos, dir);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Vector3 dir = vec3_Multiply(vec3_Normalize(vec3_Cross(cam->forward, cam->up)), moveSpeed * TimeManager.deltaTime);
		cam->pos = vec3_Add(cam->pos, dir);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		moveSpeed = moveSpeed == 12 ? 80 : 12;
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		cam->pos = (Vector3){ 0,15,5 };
	}
}
void window_content_scale_callback(GLFWwindow* window, float xscale, float yscale) {
	texW = xscale;
	texH = yscale;
}

void Engine_Init(void) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Engine.window = WindowManagerAddWindow((Vector3) { 100, 100, 0, 1 }, (Vector3) { 1280, 720, 0, 1 }, "Main", NULL);

	if (Engine.window == NULL) {
		perror("Failed to create window");
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(Engine.window->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		perror("Failed to initialize GLAD");
		glfwTerminate();
		exit(1);
	}

	glfwSetFramebufferSizeCallback(Engine.window->window, callback);
	glfwSetCursorPosCallback(Engine.window->window, mouse_callback);
	glfwSetWindowContentScaleCallback(Engine.window->window, window_content_scale_callback);
	glfwSwapInterval(1);

	ImGui_LoadGUI(Engine.window->window);

	Engine.physics = (PhysicsSystem*)malloc(sizeof(PhysicsSystem));
	PhysicsSystem_Init(Engine.physics, 10, 1000);

	Engine.render = (ModelSystem*)malloc(sizeof(ModelSystem));
	ModelSystem_Init(Engine.render, 10, 1000, ShaderInit(fileToString("default.vert"), fileToString("default.frag")));

	Engine.entity = (EntitySystem*)malloc(sizeof(EntitySystem));
	EntitySystem_Init(Engine.entity);

	Gizmo_Init(ShaderInit(fileToString("line.vert"), fileToString("line.frag")));
}

void Engine_Run(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtMemCheckpoint(&Engine.sOld);

	Engine_Init();

	Window_t* main = Engine.window;
	Shader* frameBuffer = ShaderInit(fileToString("framebuffer.vert"), fileToString("framebuffer.frag"));

	glfwSetWindowAspectRatio(main->window, 16, 9);
	glfwMakeContextCurrent(main->window);
	glfwSetInputMode(main->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Matrix4x4 proj = mat_Perspective(90.0f * DEG2RAD, 1.77777778f, 0.1f, 1000);

	stbi_set_flip_vertically_on_load(true);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	glCullFace(GL_FRONT);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Entity e = EntitySystem_Create(Engine.entity);

	PhysicsSystem_AddTransform(Engine.physics, e, &(Transform){ (Vector3) { 0, 0, 10 }, (Vector3) { 0, 0, 0 }, (Vector3) { 1, 1, 1 } });

	Model m3 = Model_Load("Miku/Miku.obj", e);
	ModelSystem_Add(Engine.render, e, &m3);

	Vector3 screenPos = (Vector3){ -0.925f, 0.85f, 0 };

	GizmoLine* r = Gizmo_AddLine(screenPos, (Vector3) { 0, 0, 0 }, (Vector3) { 1, 0, 0 }, GT_SCREEN);
	GizmoLine* u = Gizmo_AddLine(screenPos, (Vector3) { 0, 0, 0 }, (Vector3) { 0, 1, 0 }, GT_SCREEN);
	GizmoLine* f = Gizmo_AddLine(screenPos, (Vector3) { 0, 0, 0 }, (Vector3) { 0, 0, 1 }, GT_SCREEN);

	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texW, texH, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

	unsigned int RBO;
	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(main->window))
	{
		TimeManagerCalculate();
		processInput(main->window, &Engine.cam);

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glViewport(0, 0, 1920, 1080);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Matrix4x4 view = mat_LookAt(Engine.cam.pos, Engine.cam.forward, Engine.cam.right, Engine.cam.up);

		r->line.points[0].position = screenPos;
		u->line.points[0].position = screenPos;
		f->line.points[0].position = screenPos;

		r->line.points[1].position = vec3_Add(screenPos, mat_VecMultiply(mat_VecMultiply((Vector3) { 0.1f, 0, 0 }, view), proj));
		u->line.points[1].position = vec3_Add(screenPos, mat_VecMultiply(mat_VecMultiply((Vector3) { 0, 0.1f, 0 }, view), proj));
		f->line.points[1].position = vec3_Add(screenPos, mat_VecMultiply(mat_VecMultiply((Vector3) { 0, 0, 0.1f }, view), proj));

		ModelSystem_Render(Engine.render, Engine.physics, &view, &proj);
		Gizmo_Render(&view, &proj, Engine.cam.pos);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, main->scale.x, main->scale.y);

		ImGui_Render(tex, texW, texH);

		glfwSwapBuffers(main->window);
		glfwPollEvents();
	}

	Engine_Free();

	ShaderClear(frameBuffer);

	_CrtMemCheckpoint(&Engine.sNew);
	if (_CrtMemDifference(&Engine.sDiff, &Engine.sOld, &Engine.sNew))
	{
		OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
		_CrtMemDumpStatistics(&Engine.sDiff);
		OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
		_CrtMemDumpAllObjectsSince(&Engine.sOld);
		OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
		_CrtDumpMemoryLeaks();
	}
}

void Engine_Free(void) {
	PhysicsSystem_Free(Engine.physics);
	ModelSystem_Free(Engine.render);
	EntitySystem_Free(Engine.entity);
	Gizmo_Free();

	WindowManagerClear();
	glfwTerminate();

	ImGui_ClearGUI();
}