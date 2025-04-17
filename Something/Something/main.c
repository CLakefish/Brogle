#include "GameEngine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(void) {
	Engine_Run();
}

//#include <stdlib.h>
//#include <stdio.h>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include "WindowManager.h"
//#include "TimeManager.h"
//#include "Shader.h"
//#include "FileIO.h"
//
//#include "MeshComponent.h"
//#include "Camera.h"
//#include "GizmoManager.h"
//
//#include "windows.h"
//
//#include "PhysicsSystem.h"
//#include "ModelSystem.h"
//
//#define _CRTDBG_MAP_ALLOC 
//#include <stdlib.h>  
//#include <crtdbg.h>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//typedef enum GameState_t {
//	Menu,
//	Running,
//	Paused,
//} GameState_t;
//
//// TO DO:
//// Gizmos rendering system
//// - Spheres?
//// - Gizmo Text
//// // Object loading via files + meshes
//// - Improve OBJ file loading
////	 - Allow multi mesh importing for 1 file
//// - GPU Instancing
//// - shader to mesh map/dictionary
//// - More file importing support?
//// - Basic Lighting (directional, point)
//// - Deferred rendering (later)
//// Profiling
//// Serialization/deserialization
//// Physics?
//
//Vertex info[] = {
//	// Vertex,			    normal,  uvX,  uvY
//	{{-0.5f, -0.5f, -0.5f}, {1,1,1}, 0.0f, 0.0f},
//	{{ 0.5f,  0.5f, -0.5f}, {1,1,1}, 1.0f, 1.0f},
//	{{ 0.5f, -0.5f, -0.5f}, {1,1,1}, 1.0f, 0.0f},       
//	{{ 0.5f,  0.5f, -0.5f}, {1,1,1}, 1.0f, 1.0f},
//	{{-0.5f, -0.5f, -0.5f}, {1,1,1}, 0.0f, 0.0f},
//	{{-0.5f,  0.5f, -0.5f}, {1,1,1}, 0.0f, 1.0f},
//						  
//	{{-0.5f, -0.5f,  0.5f}, {1,1,1}, 0.0f, 0.0f},
//	{{ 0.5f, -0.5f,  0.5f}, {1,1,1}, 1.0f, 0.0f},
//	{{ 0.5f,  0.5f,  0.5f}, {1,1,1}, 1.0f, 1.0f},
//	{{ 0.5f,  0.5f,  0.5f}, {1,1,1}, 1.0f, 1.0f},
//	{{-0.5f,  0.5f,  0.5f}, {1,1,1}, 0.0f, 1.0f},
//	{{-0.5f, -0.5f,  0.5f}, {1,1,1}, 0.0f, 0.0f},
//						  
//	{{-0.5f,  0.5f,  0.5f}, {1,1,1}, 1.0f, 0.0f},
//	{{-0.5f,  0.5f, -0.5f}, {1,1,1}, 1.0f, 1.0f},
//	{{-0.5f, -0.5f, -0.5f}, {1,1,1}, 0.0f, 1.0f},
//	{{-0.5f, -0.5f, -0.5f}, {1,1,1}, 0.0f, 1.0f},
//	{{-0.5f, -0.5f,  0.5f}, {1,1,1}, 0.0f, 0.0f},
//	{{-0.5f,  0.5f,  0.5f}, {1,1,1}, 1.0f, 0.0f},
//
//	{{ 0.5f,  0.5f,  0.5f}, {1,1,1}, 1.0f, 0.0f},
//	{{ 0.5f, -0.5f, -0.5f}, {1,1,1}, 0.0f, 1.0f},
//	{{ 0.5f,  0.5f, -0.5f}, {1,1,1}, 1.0f, 1.0f},    
//	{{ 0.5f, -0.5f, -0.5f}, {1,1,1}, 0.0f, 1.0f},
//	{{ 0.5f,  0.5f,  0.5f}, {1,1,1}, 1.0f, 0.0f},
//	{{ 0.5f, -0.5f,  0.5f}, {1,1,1}, 0.0f, 0.0f},  
//
//	{{-0.5f, -0.5f, -0.5f}, {1,1,1}, 0.0f, 1.0f},
//	{{ 0.5f, -0.5f, -0.5f}, {1,1,1}, 1.0f, 1.0f},
//	{{ 0.5f, -0.5f,  0.5f}, {1,1,1}, 1.0f, 0.0f},
//	{{ 0.5f, -0.5f,  0.5f}, {1,1,1}, 1.0f, 0.0f},
//	{{-0.5f, -0.5f,  0.5f}, {1,1,1}, 0.0f, 0.0f},
//	{{-0.5f, -0.5f, -0.5f}, {1,1,1}, 0.0f, 1.0f},
//
//	{{-0.5f,  0.5f, -0.5f}, {1,1,1}, 0.0f, 1.0f},
//	{{ 0.5f,  0.5f,  0.5f}, {1,1,1}, 1.0f, 0.0f},
//	{{ 0.5f,  0.5f, -0.5f}, {1,1,1}, 1.0f, 1.0f},
//	{{ 0.5f,  0.5f,  0.5f}, {1,1,1}, 1.0f, 0.0f},
//	{{-0.5f,  0.5f, -0.5f}, {1,1,1}, 0.0f, 1.0f},
//	{{-0.5f,  0.5f,  0.5f}, {1,1,1}, 0.0f, 0.0f} 
//};
//unsigned int indices[6] = {
//	0, 1, 3,
//	1, 2, 3
//};
//
//void processInput(GLFWwindow* window);
//void callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//
//Camera_t cam;
//bool firstMouse = true;
//double lastX = 0, lastY = 0;
//float moveSpeed = 10;
//float pitch, yaw = -90.0f;
//
//int main()
//{
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//	_CrtMemState sOld;
//	_CrtMemState sNew;
//	_CrtMemState sDiff;
//	_CrtMemCheckpoint(&sOld);
//
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	Window_t* main = WindowManagerAddWindow((Vector3) { 100, 100, 0, 1 }, (Vector3) { 1280, 720, 0, 1 }, "Main", NULL);
//
//	glfwSetWindowAspectRatio(main->window, 16, 9);
//	glfwMakeContextCurrent(main->window);
//	glfwSetFramebufferSizeCallback(main->window, callback);
//	glfwSetCursorPosCallback(main->window, mouse_callback);
//
//	glfwSetInputMode(main->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		perror("Failed to initialize GLAD");
//		return -1;
//	}
//
//	EntityManager_Init();
//	Gizmo_Init(ShaderInit(fileToString("line.vert"), fileToString("line.frag")));
//	ModelSystem_Init(10, 100, ShaderInit(fileToString("default.vert"), fileToString("default.frag")));
//	PhysicsSystem_Init(10, 100);
//
//	Gizmo_AddLine((Vector3) { -100, 0, 0 }, (Vector3) { 100, 0, 0 }, (Vector3) { 0, 0, 1 });
//	Gizmo_AddLine((Vector3) { 0, 0, -100 }, (Vector3) { 0, 0, 100 }, (Vector3) { 1, 0, 0 });
//	Gizmo_AddLine((Vector3) { 0, -100, 0 }, (Vector3) { 0, 100, 0 }, (Vector3) { 0, 1, 0 });
//
//	Gizmo_AddBox((Vector3){-25, 0, -25}, (Vector3){ 5, 5, 5 }, (Vector3) { 1,1,1 });
//
//	// Textures
//	stbi_set_flip_vertically_on_load(true);
//
//	// OpenGL runs on a right handed system, i.e y is up and down, z is towards you (positive), right is positive x
//	Vector3 vec = { 0,0,0,1 };
//	Matrix4x4 proj = mat_Perspective(90.0f * DEG2RAD, 1.77777778f, 0.1f, 1000);
//
//	cam.pos	    = (Vector3){ 0, 0, 5.0f };
//	cam.forward = (Vector3){ 0, 0, 1.0f };
//	cam.up	    = (Vector3){ 0, 1, 0.0f };
//	cam.right	= vec3_Normalize(vec3_Cross(cam.up, cam.forward));
//
//	Entity e = EntityManager_InstantiateEntity();
//	PhysicsSystem_AddTransform(e,  &(Transform){(Vector3) { 0, 0, 10 },  (Vector3) { 0, 0, 0 }, (Vector3) { 1, 1, 1 } });
//	Entity e2 = EntityManager_InstantiateEntity();
//	PhysicsSystem_AddTransform(e2, &(Transform){(Vector3) { 0, 2, 10 },  (Vector3) { 0, 0, 0 }, (Vector3) { 1, 1, 1 } });
//	Entity e3 = EntityManager_InstantiateEntity();
//	PhysicsSystem_AddTransform(e3, &(Transform){(Vector3) { -5, 0, 10 }, (Vector3) { 0, 0, 0 }, (Vector3) { 1, 1, 1 } });
//	Entity e4 = EntityManager_InstantiateEntity();
//	PhysicsSystem_AddTransform(e4, &(Transform){(Vector3) { 5, 0, 10 },  (Vector3) { 0, 0, 0 }, (Vector3) { 1, 1, 1 } });
//
//	Texture tex = Texture_Init("IMG_7749.jpg");
//	Mesh mesh   = Mesh_Init(36, info, 6, indices, tex);
//
//	Texture tex2 = Texture_Init("img_MIKU_us.png");
//	Mesh mesh2   = Mesh_Init(36, info, 6, indices, tex2);
//
//	Model m = Model_Init(&mesh, e);
//	ModelSystem_Add(e, &m);
//	Model m2 = Model_Init(&mesh2, e2);
//	ModelSystem_Add(e2, &m2);
//	Model m3 = Model_Load("Miku/Miku.obj", e3);
//	ModelSystem_Add(e3, &m3);
//	Model m4 = Model_Load("Person/man.obj", e4);
//	ModelSystem_Add(e4, &m4);
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_FRONT);
//
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_BLEND);
//
//	while (!glfwWindowShouldClose(main->window))
//	{
//		TimeManagerCalculate();
//		processInput(main->window);
//
//		glClearColor(0.1f, 0, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		Matrix4x4 view = mat_LookAt(cam.pos, cam.forward, cam.right, cam.up);
//
//		Transform* t = PhysicsSystem_GetTransform(e4);
//		t->eulers   = (Vector3){ 0, TimeManager.time, 0 };
//		t->position = (Vector3){ 10, sinf(TimeManager.time), sinf(TimeManager.time) * 5 };
//
//		ModelSystem_Render(&view, &proj);
//		Gizmo_RenderTop(&view, &proj, cam.pos);
//
//		glfwSwapBuffers(main->window);
//		glfwPollEvents();
//	}
//
//	PhysicsSystem_Free();
//	EntityManager_Free();
//	ModelSystem_Free();
//	Gizmo_Free();
//
//	WindowManagerClear();
//	glfwTerminate();
//
//	_CrtMemCheckpoint(&sNew);
//	if (_CrtMemDifference(&sDiff, &sOld, &sNew))
//	{
//		OutputDebugString(L"-----------_CrtMemDumpStatistics ---------");
//		_CrtMemDumpStatistics(&sDiff);
//		OutputDebugString(L"-----------_CrtMemDumpAllObjectsSince ---------");
//		_CrtMemDumpAllObjectsSince(&sOld);
//		OutputDebugString(L"-----------_CrtDumpMemoryLeaks ---------");
//		_CrtDumpMemoryLeaks();
//	}
//
//	return 0;
//}
//
//void processInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetInputMode(window, GLFW_CURSOR, glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
//		firstMouse = true;
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
//		cam.pos = vec3_Add(cam.pos, vec3_Multiply((Vector3) { 0, 1, 0 }, moveSpeed * TimeManager.deltaTime));
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
//		cam.pos = vec3_Subtract(cam.pos, vec3_Multiply((Vector3) { 0, 1, 0 }, moveSpeed * TimeManager.deltaTime));
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
//		cam.pos = vec3_Subtract(cam.pos, vec3_Multiply(cam.forward, moveSpeed * TimeManager.deltaTime));
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
//		cam.pos = vec3_Add(cam.pos, vec3_Multiply(cam.forward, moveSpeed * TimeManager.deltaTime));
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
//		Vector3 dir = vec3_Multiply(vec3_Normalize(vec3_Cross(cam.forward, cam.up)), moveSpeed * TimeManager.deltaTime);
//		cam.pos = vec3_Subtract(cam.pos, dir);
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
//		Vector3 dir = vec3_Multiply(vec3_Normalize(vec3_Cross(cam.forward, cam.up)), moveSpeed * TimeManager.deltaTime);
//		cam.pos = vec3_Add(cam.pos, dir);
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
//		moveSpeed = moveSpeed == 12 ? 80 : 12;
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
//		cam.pos = (Vector3){0,15,5};
//	}
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = lastX - xpos;
//	float yoffset = ypos - lastY;
//	lastX = xpos;
//	lastY = ypos;
//
//	float sensitivity = 0.1f;
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	yaw   += xoffset;
//	pitch += yoffset;
//
//	CLAMP(pitch, -89.9f, 89.9f);
//
//	Vector3 dir = {0,0,0};
//	dir.x = cosf(yaw   * DEG2RAD) * cosf(pitch * DEG2RAD);
//	dir.y = sinf(pitch * DEG2RAD);
//	dir.z = sinf(yaw   * DEG2RAD) * cosf(pitch * DEG2RAD);
//	cam.forward = vec3_Normalize(dir);
//	cam.right   = vec3_Normalize(vec3_Cross(cam.forward, (Vector3) { 0, 1, 0 }));
//	cam.up	    = vec3_Normalize(vec3_Cross(cam.right, cam.forward));
//}
//
//void callback(GLFWwindow* window, int width, int height)
//{
//	windowManager.ptr[0].scale = (Vector3){ width, height, 0 };
//	glViewport(0, 0, width, height);
//}