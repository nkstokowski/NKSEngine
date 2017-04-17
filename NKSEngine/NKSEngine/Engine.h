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
#include "Model.h"
#include <ctime>

using namespace std;

class Engine
{
private:
	static GLFWwindow* GLFWwindowPtr;
	static Shader myShader;
	static Camera myCamera;
	static float t0, t, dt, speed;
	static Model myModel;
public:
	//static Timer timer;
	static bool start();
	static void stop();
	static bool bufferModels();
	static void update();
	static void render();
	static bool shouldClose();
	static bool loadTexture();
	Engine();
	virtual ~Engine();
};

