#include <stdlib.h>
#include "Engine.h"
#include "GLDebug.h"

Timer Engine::myTimer;
GLFWwindow* Engine::GLFWwindowPtr;
Shader Engine::myShader;
Camera Engine::myCamera;
//Skybox* Engine::mySkybox;

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

	vector<const GLchar*> faces;
	faces.push_back("textures/hw_morning/morning_rt.tga");
	faces.push_back("textures/hw_morning/morning_lf.tga");
	faces.push_back("textures/hw_morning/morning_up.tga");
	faces.push_back("textures/hw_morning/morning_dn.tga");
	faces.push_back("textures/hw_morning/morning_bk.tga");
	faces.push_back("textures/hw_morning/morning_ft.tga");
	//Model* skyboxMod = new Model("models/box.obj");
	//Cubemap* skyboxTex = new Cubemap();
	//mySkybox->setModel(skyboxMod);
	//mySkybox->setTexture(skyboxTex);
	//skyboxMod->buffer();
	//skyboxTex->load(faces);


	glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	int w, h;
	glfwGetWindowSize(GLFWwindowPtr, &w, &h);
	glfwSetCursorPos(GLFWwindowPtr, w / 2, h / 2);

	// Uploading materials
	glm::vec4 matData;
	matData.x = 0.6f;
	matData.y = 0.6f;
	matData.z = 0.6f;
	matData.w = 16.0f;

	glm::vec3 lightloc = { 0, 5, 1 };

	glUniform3f(8, lightloc.x, lightloc.y, lightloc.z);
	glUniform4f(6, matData.x, matData.y, matData.z, matData.w);
	glClear(GL_COLOR_BUFFER_BIT);

	return true;
}

void Engine::stop()
{
	myShader.unload();
	glfwTerminate();
}

bool Engine::bufferModels()
{
	return true;
}

void Engine::update()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	
	myCamera.update();

	float timeval = (float)glfwGetTime();
	glUniform1fv(5, 1, &timeval);

	myCamera.uploadLocation(7);

	glfwSwapBuffers(GLFWwindowPtr);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);
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



Engine::Engine()
{
}


Engine::~Engine()
{
}
