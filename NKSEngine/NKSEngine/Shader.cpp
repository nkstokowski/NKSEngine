#include "Shader.h"
#include <fstream>
#include <iostream>

using namespace std;

bool Shader::load()
{
	if (!compile(GL_VERTEX_SHADER)) {
		printf("Error compiling vertex shader.\n");
		return false;
	}
	if (!compile(GL_FRAGMENT_SHADER)) {
		printf("Error compiling fragment shader.\n");
		return false;
	}

	program = glCreateProgram();
	glAttachShader(program, vprogram);
	glAttachShader(program, fprogram);
	glLinkProgram(program);

	GLint result;
	int length;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE) {
		printf("Link failed.\n");
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		GLchar* info = new GLchar[length];
		glGetProgramInfoLog(program, length, 0, info);
		printf("Info log:\n%s\n", info);
		glDeleteProgram(program);
		delete[] info;
		glDeleteShader(vprogram);
		glDeleteShader(fprogram);
		return false;
	}
	return true;
}

bool Shader::compile(GLenum shaderType)
{
	string fn;
	int length;

	if (shaderType == GL_VERTEX_SHADER) {
		fn = filenamev;
	}
	else if(shaderType == GL_FRAGMENT_SHADER) {
		fn = filenamef;
	}
	else {
		printf("No shader file known for this type.\n");
		return false;
	}
	//printf("Filename used: %s\n", fn.c_str());
	ifstream strm(fn, ios::binary);
	if (!strm.is_open()) {
		printf("Error opening file.\n");
		return false;
	}

	strm.seekg(0, ios::end);
	length = (int)strm.tellg();
	strm.seekg(0, ios::beg);

	char* filedata = new char[length + 1];
	filedata[length] = '\0';
	strm.read(filedata, length);
	strm.close();

	GLuint index;
	index = glCreateShader(shaderType);
	glShaderSource(index, 1, &filedata, 0);
	glCompileShader(index);
	delete[] filedata;

	GLint result;
	glGetShaderiv(index, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		printf("Compile failed.\n");
		glGetShaderiv(index, GL_INFO_LOG_LENGTH, &length);
		GLchar* info = new GLchar[length];
		glGetShaderInfoLog(index, length, 0, info);
		printf("Info log:\n%s\n", info);
		glDeleteShader(index);
		delete[] info;
		return false;
	}
	if (shaderType == GL_VERTEX_SHADER) {
		vprogram = index;
	}
	else if (shaderType == GL_FRAGMENT_SHADER) {
		fprogram = index;
	}
	return true;

}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::unload()
{
	glDeleteProgram(program);
	glDeleteShader(vprogram);
	glDeleteShader(fprogram);

	program = 0;
	vprogram = 0;
	fprogram = 0;
}

Shader::Shader()
{
}


Shader::~Shader()
{
}
