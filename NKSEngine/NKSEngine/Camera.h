#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include "Object.h"

using namespace std;

class Camera :
	public Object
{
private:
	glm::mat4 worldView;
	glm::mat3 rotMat;
	float t0, t, dt, fovy, zoom, aspect, zNear, zFar, speed, sensativity;
	int width, height;
	GLFWwindow* window;
public:
	glm::vec3 rotation, location, velocity, eye, center, up;
	bool debugging;
	void uploadLocation(int index);
	void move();
	void turn();
	void start();
	void update();
	void upload();
	void setWindow(GLFWwindow* windowPtr);
	Camera();
	virtual ~Camera();
};

