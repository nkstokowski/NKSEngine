#pragma once
#include "Object.h"
#include "Timer.h"
#include <string>
#include <iostream>
#include <vector>

class Quad :
	public Object
{
private:
	GLuint vertArr;
	unsigned int vertCount;
public:
	Quad();
	void update() override;
	bool loadModel();
	~Quad();
};

