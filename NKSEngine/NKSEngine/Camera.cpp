#include "Camera.h"


void Camera::uploadLocation(int index)
{
	glUniform3f(index, location.x, location.y, location.z);
}

void Camera::move()
{
	glm::vec3 direction;

	if (glfwGetKey(window, GLFW_KEY_LEFT) || glfwGetKey(window, GLFW_KEY_A)) {
		direction.x -= 1;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) || glfwGetKey(window, GLFW_KEY_D)) {
		direction.x += 1;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) || glfwGetKey(window, GLFW_KEY_W)) {
		direction.z -= 1;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) || glfwGetKey(window, GLFW_KEY_S)) {
		direction.z += 1;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
		speed = 5.0f;
	}
	else {
		speed = 2.0f;
	}

	if (direction != glm::vec3()) {
		direction = glm::normalize(direction);
	}

	velocity = rotMat * direction * speed;
	location += dt * velocity;

}

void Camera::turn()
{
	double x, y;
	float pi = 3.14159;
	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &x, &y);

	rotation.y += sensativity * (width * .5f - x);
	rotation.x += sensativity * (height * .5f - y);
	rotation.x = glm::clamp(rotation.x, -.5f * pi, .5f * pi);

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

	eye = location;
	center = eye + rotMat * glm::vec3(0, 0, -1);
	up = rotMat * glm::vec3(0, 1, 0);

}

void Camera::update()
{
	t0 = t;
	t = (float)glfwGetTime();
	dt = t - t0;

	move();
	turn();

	eye = location;
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
	location = { 0, 0, 2 };
	rotation = { 0, 0, 0 };
}


Camera::~Camera()
{
}
