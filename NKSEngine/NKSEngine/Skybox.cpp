#include "Skybox.h"

bool Skybox::render()
{
	cubemap->render();
	mod->render();
	return true;
}

Skybox::Skybox()
{
}


Skybox::~Skybox()
{
}
