#include "Object.h"
#include <string>
#include <iostream>


Object::Object()
{
	tag = "default";
}

void Object::update()
{
}

void Object::render()
{
	printf("Rendering %s\n", tag.c_str());
}


Object::~Object()
{
}
