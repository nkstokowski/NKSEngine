#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Timer.h"
#include "Shader.h"
#include "Camera.h"
#include "Object.h"
#include "Skybox.h"
#include <ctime>

using namespace std;

class Engine
{
private:
	static Shader myShader;
	static float t0, t, dt, speed;
	//static Skybox* mySkybox;
public:
	static Camera myCamera;
	static GLFWwindow* GLFWwindowPtr;
	static Timer myTimer;
	static bool start();
	static void stop();
	static bool bufferModels();
	static void update();
	static void render();
	static bool shouldClose();
	Engine();
	virtual ~Engine();
};