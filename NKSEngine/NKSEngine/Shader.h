#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Shader
{
public:
	GLuint program, vprogram, fprogram;
	string filenamev = "shaders/V4/vShader.glsl";
	string filenamef = "shaders/V4/fShader.glsl";
	bool load();
	bool compile(GLenum shaderType);
	void use();
	void unload();
	Shader();
	virtual ~Shader();
};

