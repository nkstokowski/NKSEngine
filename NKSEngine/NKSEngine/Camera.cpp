#include "Camera.h"


void Camera::uploadLocation(int index)
{
	glUniform3f(index, location.x, location.y, location.z);
}

void Camera::move()
{
	glm::vec3 direction;
	bool pressed = false;

	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		//direction.x -= 1;
		transform.force += glm::vec3(-1, 0, 0);
		pressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		//direction.x += 1;
		transform.force += glm::vec3(1, 0, 0);
		pressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_UP)) {
		//direction.z -= 1;
		transform.force += glm::vec3(0, 0, -1);
		pressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		//direction.z += 1;
		transform.force += glm::vec3(0, 0, 1);
		pressed = true;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) && debugging) {
		speed = 5.0f;
	}
	else {
		speed = 2.0f;
	}

	if (direction != glm::vec3()) {
		direction = glm::normalize(direction);
		transform.force = glm::normalize(transform.force);
	}

	/*if (!pressed) {
		transform.force = { 0, 0, 0 };
	}*/

	//velocity from force
	transform.velocity = rotMat * (transform.force / transform.mass) * speed;
	//location from velocity
	transform.location += transform.velocity * dt;

	transform.force = { 0, 0, 0 };

	//velocity = rotMat * direction * speed;
	//location += dt * velocity;

}

void Camera::turn()
{
	double x, y;
	float pi = 3.14159;
	/*glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &x, &y);

	rotation.y += sensativity * (width * .5f - x);
	rotation.x += sensativity * (height * .5f - y);
	rotation.x = glm::clamp(rotation.x, -.5f * pi, .5f * pi);*/

	glfwSetCursorPos(window, width * .5f, height * .5f);
	rotMat = glm::mat3(glm::yawPitchRoll(rotation.y, rotation.x, rotation.z));
}

void Camera::start()
{
	worldView = glm::mat4();

	t0 = (float)glfwGetTime();
	t = (float)glfwGetTime();
	dt = t - t0;

	fovy = 3.14159f * .4f / zoom;
	aspect = (float)width / (float)height;
	zNear = .01f;
	zFar = 1000.0f;

	rotMat = (glm::mat3)glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);

	//eye = location;
	eye = transform.location;
	center = eye + rotMat * glm::vec3(0, 0, -1);
	up = rotMat * glm::vec3(0, 1, 0);

}

void Camera::update()
{
	t0 = t;
	t = (float)glfwGetTime();
	dt = t - t0;

	if (debugging) {
		move();
		turn();
	}
	else {
		move();
	}

	//eye = location;
	eye = transform.location;
	center = eye + rotMat * glm::vec3(0, 0, -1);
	up = rotMat * glm::vec3(0, 1, 0);

	worldView = glm::perspective(fovy, aspect, zNear, zFar) * glm::lookAt(eye, center, up);
	upload();

}

void Camera::upload()
{
	glUniformMatrix4fv(4, 1, GL_FALSE, &worldView[0][0]);
}

void Camera::setWindow(GLFWwindow* windowPtr) 
{
	window = windowPtr;
}

Camera::Camera()
{
	width = 800;
	height = 600;
	zoom = 1.0f;
	speed = 2.0f;
	sensativity = 0.005;
	//location = { 0, 0, 7 };
	transform.location = { 0, 0, 7 };
	rotation = { 0, 0, 0 };
	debugging = false;
}


Camera::~Camera()
{
}
