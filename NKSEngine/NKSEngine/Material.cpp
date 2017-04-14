#include "Material.h"



bool Material::lighting()
{
	//L = glm::normalize(lightloc - worldloc);
	//V = glm::normalize(cameraloc - worldloc);
	//H = glm::normalize(L + V);

	return false;
}

bool Material::upload()
{
	return false;
}

Material::Material()
{
	lightloc = glm::vec3(0.0f, 10.0f, 0.0f);
	alpha = 16.0f;
}


Material::~Material()
{
}
