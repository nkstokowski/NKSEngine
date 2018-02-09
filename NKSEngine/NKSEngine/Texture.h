#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <string>

using namespace std;

class Texture
{
private:
public:
	GLuint textID;
	virtual bool render();
	bool unload();
	string textfile;
	virtual bool load(string textFile);
	Texture();
	virtual ~Texture();
};

