#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Engine.h"


using namespace std;

void loadAssets(vector<Model> models) {
	for (auto &i : models) {
		i.buffer();
	}
}

void unloadAssets(vector<Model> models) {
	for (auto &i : models) {
		i.unload();
	}
}

int main() {

	Engine::start();
	vector<Object> objects;
	float dt;
	float cDrag = -10;
	float epsilon = .001f;
	glm::vec3 cGrav = { 0, -9.81, 0 };

	Model* quadModel = new Model("models/quad.obj");
	quadModel->buffer();

	Model* myModel = new Model("models/box.obj");
	myModel->buffer();

	Model* goalModel = new Model("models/sphere.obj");
	goalModel->buffer();

	vector<Texture*> cubes;

	// Load all the textures for the numbered cube
	Texture* testTexture = new Texture();
	testTexture->load("textures/TestTexture.png");
	Texture* zeroTexture = new Texture();
	zeroTexture->load("textures/cubeZero.png");
	cubes.push_back(zeroTexture);
	Texture* oneTexture = new Texture();
	oneTexture->load("textures/cubeOne.png");
	zeroTexture->load("textures/cubeZero.png");
	cubes.push_back(oneTexture);
	Texture* twoTexture = new Texture();
	twoTexture->load("textures/cubeTwo.png");
	zeroTexture->load("textures/cubeZero.png");
	cubes.push_back(twoTexture);
	Texture* threeTexture = new Texture();
	threeTexture->load("textures/cubeThree.png");
	zeroTexture->load("textures/cubeZero.png");
	cubes.push_back(threeTexture);
	int textInd = 0;

	Texture* goalTexture = new Texture();
	goalTexture->load("textures/goaltexture.png");
	
	// Load all the objects
	Object floor;
	Texture* floorTexture = new Texture();
	floorTexture->load("textures/floor_conc.jpg");
	floor.setModel(myModel);
	floor.setTexture(floorTexture);
	floor.transform.location = glm::vec3(0, -2.8, 1.0);
	floor.transform.size = glm::vec3(5, 1.8, 3);
	floor.collider = floor.aabb;
	bool grounded = false;

	Object plat1;
	plat1.setModel(myModel);
	plat1.setTexture(floorTexture);
	plat1.transform.location = glm::vec3(-2, -2.2, -4.0);
	plat1.transform.size = glm::vec3(3, 1, 1);
	plat1.collider = plat1.aabb;
	bool plat1Grounded = false;
	bool plat1movingLeft = true;

	Object plat2;
	plat2.setModel(myModel);
	plat2.setTexture(floorTexture);
	plat2.transform.location = glm::vec3(0, -2.2, -7.0);
	plat2.transform.size = glm::vec3(3, 1, 1);
	plat2.collider = plat2.aabb;
	bool plat2Grounded = false;
	bool plat2movingLeft = false;

	Object plat3;
	plat3.setModel(myModel);
	plat3.setTexture(floorTexture);
	plat3.transform.location = glm::vec3(3, -2.2, -10.0);
	plat3.transform.size = glm::vec3(3, 1, 1);
	plat3.collider = plat3.aabb;
	bool plat3Grounded = false;
	bool plat3movingLeft = true;

	Object leftborder;
	leftborder.setModel(quadModel);
	leftborder.setTexture(testTexture);
	leftborder.transform.location = glm::vec3(-20, 0, -10);
	leftborder.transform.size = glm::vec3(10, 10, 10);
	leftborder.transform.rotation = { 0, 1.6, 0 };
	leftborder.collider = leftborder.aabb;

	Object rightborder;
	rightborder.setModel(quadModel);
	rightborder.setTexture(testTexture);
	rightborder.transform.location = glm::vec3(20, 0, -10);
	rightborder.transform.size = glm::vec3(10, 10, 10);
	rightborder.transform.rotation = { 0, 1.6, 0 };
	rightborder.collider = rightborder.aabb;

	Object deathborder;
	deathborder.setModel(quadModel);
	deathborder.setTexture(testTexture);
	deathborder.transform.location = glm::vec3(-10.0, -30.0, -5.0);
	deathborder.transform.size = glm::vec3(40, 20, 40);
	deathborder.transform.rotation = { 1.6, 0, 0 };
	deathborder.collider = deathborder.aabb;

	Object end;
	end.setModel(myModel);
	end.setTexture(floorTexture);
	end.transform.location = glm::vec3(0, -2.8, -15.0);
	end.transform.size = glm::vec3(5, 1.8, 3);
	end.collider = end.aabb;
	bool endGrounded = false;

	Object goal;
	goal.setModel(goalModel);
	goal.setTexture(goalTexture);
	goal.transform.size = { 0.7, 0.7, 0.7 };
	goal.transform.location = glm::vec3(0, 0, -15);
	goal.collider = goal.sphere;
	
	Object character;
	character.setModel(myModel);
	character.setTexture(zeroTexture);
	character.transform.location = { 0, 5, 1 };
	character.transform.size = glm::vec3(.3, .3, .3);
	character.collider = character.aabb;
	//character.debug = true;
	glm::vec3 charRunX = { 40, 0, 0 };
	glm::vec3 charRunZ = { 0, 0, 40 };
	glm::vec3 charStopX = { 40, 0, 0 };
	glm::vec3 charStopZ = { 0, 0, 40 };
	glm::vec3 charJump = { 0, 6, 0 };
	float dirStopX = glm::sign(character.transform.velocity.x);
	float magStopX = min(1.0f, fabs(character.transform.velocity.x));
	float dirStopZ = glm::sign(character.transform.velocity.z);
	float magStopZ = min(1.0f, fabs(character.transform.velocity.z));
	float charMaxSpeed = 10.0;
	//character.angle = 90;

	// Initial camera data.
	dt = Engine::myTimer.update();
	Engine::myCamera.debugging = true;
	Engine::myCamera.transform.location = {13.516, 8.895, 1.299};
	Engine::myCamera.rotation = {-0.685, 0.895, 0};
	Engine::myCamera.update();
	Engine::myCamera.debugging = false;
	glm::vec3 cameraMove = { 10.0, 2.0, 0.0 };

	// Game Loop
	while (!Engine::shouldClose()) {
		dt = Engine::myTimer.update();

		// Character Movement
		// Collisions
		grounded = false;
		plat1Grounded = false;
		plat2Grounded = false;
		plat3Grounded = false;
		if ((character.collidesWith(floor) || character.collidesWith(end)) && !grounded && character.transform.location.y > floor.transform.location.y + floor.transform.size.y) {
			grounded = true;
			plat1Grounded = false;
			//printf("Colliding with starting platform.\n");
		}
		if (character.collidesWith(plat1) && !grounded && character.transform.location.y > plat1.transform.location.y + plat1.transform.size.y) {
			grounded = true;
			plat1Grounded = true;
			//printf("Colliding with starting platform.\n");
		}
		if (character.collidesWith(plat2) && !grounded && character.transform.location.y > plat2.transform.location.y + plat2.transform.size.y) {
			grounded = true;
			plat2Grounded = true;
			//printf("Colliding with starting platform.\n");
		}
		if (character.collidesWith(plat3) && !grounded && character.transform.location.y > plat3.transform.location.y + plat3.transform.size.y) {
			grounded = true;
			plat3Grounded = true;
			//printf("Colliding with starting platform.\n");
		}

		if (character.collidesWith(goal)) {
			if (textInd < cubes.size() - 1) {
				textInd++;
				character.setTexture(cubes[textInd]);
			}
			character.transform.velocity = { 0, 0, 0 };
			character.transform.location = { 0, 5, 1 };
			Engine::myCamera.debugging = true;
			Engine::myCamera.transform.location = { 13.516, 8.895, 1.299 };
			Engine::myCamera.rotation = { -0.685, 0.895, 0 };
			Engine::myCamera.update();
			Engine::myCamera.debugging = false;
			
		}

		if (character.collidesWith(deathborder)) {
			//printf("Colliding with death border.\n");
			character.transform.velocity = { 0, 0, 0 };
			character.transform.location = { 0, 5, 1 };
			Engine::myCamera.debugging = true;
			Engine::myCamera.transform.location = { 13.516, 8.895, 1.299 };
			Engine::myCamera.rotation = { -0.685, 0.895, 0 };
			Engine::myCamera.update();
			Engine::myCamera.debugging = false;
		}

		// Platform bouncing
		if (plat1.collidesWith(leftborder)) {
			plat1movingLeft = false;
		}
		if (plat1.collidesWith(rightborder)) {
			plat1movingLeft = true;
		}
		if (plat2.collidesWith(leftborder)) {
			plat2movingLeft = false;
		}
		if (plat2.collidesWith(rightborder)) {
			plat2movingLeft = true;
		}
		if (plat3.collidesWith(leftborder)) {
			plat3movingLeft = false;
		}
		if (plat3.collidesWith(rightborder)) {
			plat3movingLeft = true;
		}

		//Running Force
		if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_D)) {
			character.transform.force += charRunX;
			if (plat1Grounded || plat2Grounded || plat3Grounded) character.transform.force += charRunX * 30.0f;
		}
		if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_A)) {
			character.transform.force -= charRunX;
			if (plat1Grounded || plat2Grounded || plat3Grounded) character.transform.force -= charRunX * 30.0f;
		}
		if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_S)) {
			character.transform.force += charRunZ;
			if (Engine::myCamera.transform.location.x > 13.5 && Engine::myCamera.transform.location.y > 8.8) {
				Engine::myCamera.transform.force -= cameraMove;
			}
		}
		if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_W)) {
			character.transform.force -= charRunZ;
			if (character.transform.force.x > 20.0f) character.transform.force.x = 20.0f;
			if (character.transform.force.x < -20.0f) character.transform.force.x = -20.0f;
			if (Engine::myCamera.transform.location.x < 19.3 && Engine::myCamera.transform.location.y < 10.5) {
				Engine::myCamera.transform.force += cameraMove;
			}
		}
		// Jumping Force
		if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_SPACE) && grounded) character.transform.velocity += charJump;
		character.transform.force += cDrag * character.transform.velocity;  // Drag
		character.transform.force += character.transform.mass * cGrav;		// Grav
		dirStopX = glm::sign(character.transform.velocity.x);
		magStopX = min(1.0f, fabs(character.transform.velocity.x));
		dirStopZ = glm::sign(character.transform.velocity.z);
		magStopZ = min(1.0f, fabs(character.transform.velocity.z));
		// Stopping Fprce
		if (!glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_A) && !glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_D) && grounded) {
			character.transform.force -= charStopX * dirStopX * magStopX;
		}
		if (!glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_W) && !glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_S) && grounded) {
			character.transform.force -= charStopZ * dirStopZ * magStopZ;
		}
		//Landing Force
		if (character.transform.velocity.y < 0 && grounded) {
			character.transform.velocity.y = 0;
			if (plat1Grounded || plat2Grounded || plat3Grounded) {
				character.transform.location.y = character.transform.size.y + plat1.transform.location.y + plat1.transform.size.y - epsilon;
			}
			else {
				character.transform.location.y = character.transform.size.y + floor.transform.location.y + floor.transform.size.y - epsilon;
			}
		}
		// Normal Force
		if (grounded) {
			character.transform.force -= character.transform.mass * -cGrav;
			if (plat1Grounded) {
				character.transform.velocity.x = plat1.transform.velocity.x;
			}
			else if (plat2Grounded) {
				character.transform.velocity.x = plat2.transform.velocity.x;
			}
			else if (plat3Grounded) {
				character.transform.velocity.x = plat3.transform.velocity.x;
			}
		}

		// End Character Movement

		// Platform Movement
		if (plat1movingLeft) {
			plat1.transform.velocity = { -3, 0, 0 };
		}
		else {
			plat1.transform.velocity = { 3, 0, 0 };
		}
		if (plat2movingLeft) {
			plat2.transform.velocity = { -3, 0, 0 };
		}
		else {
			plat2.transform.velocity = { 3, 0, 0 };
		}
		if (plat3movingLeft) {
			plat3.transform.velocity = { -3, 0, 0 };
		}
		else {
			plat3.transform.velocity = { 3, 0, 0 };
		}

		// Goal Movement
		goal.transform.rotation += glm::vec3(0, 0.02, 0);

		// Camera Debugging - Non Functional
		//if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_Z)) Engine::myCamera.debugging = true;
		//if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_X)) Engine::myCamera.debugging = false;

		// Update Objects
		// Could use a vector, but currently this would be the only place it is used.
		character.update(dt);
		plat1.update(dt);
		plat2.update(dt);
		plat3.update(dt);
		end.update(dt);
		floor.update(dt);
		leftborder.update(dt);
		rightborder.update(dt);
		deathborder.update(dt);
		goal.update(dt);
		
		// Rendering

		//leftborder.render();
		//rightborder.render();
		//deathborder.render();
		if (character.transform.location.y < floor.transform.location.y) {
			character.render();  // Render character behind platforms
		}
		end.render();
		plat3.render();
		plat2.render();
		plat1.render();
		floor.render();
		if (character.transform.location.x > goal.transform.location.x) {
			goal.render();	// Render goal behind character
		}
		if (character.transform.location.y > floor.transform.location.y) {
			character.render();  // Render character in front of platforms
		}
		if (character.transform.location.x <= goal.transform.location.x) {
			goal.render();	// Render goal in front of character
		}

		if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_P)) {
			printf("Camera location at x: %f, y: %f, z: %f\n", Engine::myCamera.transform.location.x, Engine::myCamera.transform.location.y, Engine::myCamera.transform.location.z);
			//printf("Camera rotation at x: %f, y: %f, z: %f\n", Engine::myCamera.rotation.x, Engine::myCamera.rotation.y, Engine::myCamera.rotation.z);
			//printf("Camera force at x: %f, y: %f, z: %f\n", Engine::myCamera.transform.force.x, Engine::myCamera.transform.force.y, Engine::myCamera.transform.force.z);
			//printf("Camera velocity at x: %f, y: %f, z: %f\n", Engine::myCamera.transform.velocity.x, Engine::myCamera.transform.velocity.y, Engine::myCamera.transform.velocity.z);
		}

		//printf("Character location at y: %f\n", character.transform.location.y);
		//if(grounded) printf("Grounded: True\n");
		//else printf("Grounded: False\n");


		Engine::update();
	}
	
	//unloadAssets(models);
	Engine::stop();	

	return 0;
}