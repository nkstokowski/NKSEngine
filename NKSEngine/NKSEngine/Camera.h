#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace std;

class Camera
{
private:
	glm::mat4 worldView;
	glm::mat3 rotMat;
	glm::vec3 rotation, location, velocity, eye, center, up;
	float t0, t, dt, fovy, zoom, aspect, zNear, zFar, speed, sensativity;
	int width, height;
	GLFWwindow* window;
public:
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

