#pragma once
#include "Texture.h"
#include <vector>
class Cubemap :
	public Texture
{
private:
	GLuint textID;
public:
	bool load(vector<const GLchar*> f);
	bool render();
	Cubemap();
	virtual ~Cubemap();
};

