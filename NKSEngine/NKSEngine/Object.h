#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <string>
using namespace std;

class Object
{
public:
	string tag;
	Object();
	virtual void update();
	void render();
	virtual ~Object();
};

