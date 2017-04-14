#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

using namespace std;

class Material
{
private:
	float ambient, diffuse, specular, alpha;
	glm::vec3 L, V, H, N, lightloc;
public:
	bool lighting();
	bool upload();
	Material();
	~Material();
};

