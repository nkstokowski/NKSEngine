#pragma once
#include "Object.h"
#include "Cubemap.h"

class Skybox :
	public Object
{
private:
	Cubemap* cubemap;
public:
	bool render();
	Skybox();
	virtual ~Skybox();
};

