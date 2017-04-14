#include <string>
#include <iostream>
#include <vector>
#include "Engine.h"
#include "Quad.h"

using namespace std;

int main() {

	Engine::start();
	//Quad myQuad;
	//myQuad.loadModel();
	Engine::bufferModels();

	while (!Engine::shouldClose()) {
		//myQuad.update();
		Engine::update();
	}
	
	Engine::stop();	

	return 0;
}
