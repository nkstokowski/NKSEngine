#include <stdlib.h>
#include "Engine.h"
#include "Timer.h"
#include "GLDebug.h"

//Timer Engine::timer;
GLFWwindow* Engine::GLFWwindowPtr;
Shader Engine::myShader;
Camera Engine::myCamera;
Model Engine::myModel;

bool Engine::start()
{
	if (glfwInit() != GL_TRUE) {
		return false;
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//initDebug();
	GLFWwindowPtr = glfwCreateWindow(800, 600, "Nick Stokowski DSA1 Engine", NULL, NULL);

	if (GLFWwindowPtr != nullptr) {
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else {
		glfwTerminate();
		return false;
	}

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}

	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	if (!myShader.load()) {
		return false;
	}
	
	myShader.use();
	float scale = 1.0;
	glUniform1fv(3, 1, &scale);

	myCamera.setWindow(GLFWwindowPtr);
	myCamera.start();
	myCamera.upload();

	glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	int w, h;
	glfwGetWindowSize(GLFWwindowPtr, &w, &h);
	glfwSetCursorPos(GLFWwindowPtr, w / 2, h / 2);

	// Uploading materials
	glm::vec4 matData;
	matData.x = 0.1f;
	matData.y = 1.0f;
	matData.z = 0.0f;
	matData.w = 16.0f;

	glm::vec3 lightloc = glm::vec3(1.0f, 10.0f, 0.0f);

	glUniform3f(8, lightloc.x, lightloc.y, lightloc.z);
	glUniform4f(6, matData.x, matData.y, matData.z, matData.w);

	loadTexture();

	return true;
}

void Engine::stop()
{
	myShader.unload();
	glfwTerminate();
}

bool Engine::bufferModels()
{
	myModel.buffer("models/teapot.obj");
	return true;
}

void Engine::update()
{

	glClear(GL_COLOR_BUFFER_BIT);

	myModel.render();

	myCamera.update();

	float timeval = (float)glfwGetTime();
	glUniform1fv(5, 1, &timeval);

	myCamera.uploadLocation(7);

	glfwSwapBuffers(GLFWwindowPtr);
	glfwPollEvents();

}

void Engine::render() {

}

bool Engine::shouldClose()
{
	if (glfwWindowShouldClose(GLFWwindowPtr)) {
		return true;
	}

	if (glfwGetKey(GLFWwindowPtr, GLFW_KEY_ESCAPE)) {
		return true;
	}

	return false;
}

bool Engine::loadTexture()
{
	FreeImage_GetFileType();
	FIBITMAP* image = FreeImage_Load();
}

Engine::Engine()
{
}


Engine::~Engine()
{
}
