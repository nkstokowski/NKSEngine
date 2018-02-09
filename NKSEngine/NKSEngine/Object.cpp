#include "Object.h"
#include <string>
#include <iostream>


Object::Object()
{
	tag = "default";
	transform.location = glm::vec3(0, 0, 0);
	transform.size = glm::vec3(1.0, 1.0, 1.0);
	transform.rotation = glm::vec3(0, 0, 0);
	transform.force = glm::vec3(0, 0, 0);
	transform.velocity = glm::vec3(0, 0, 0);
	transform.mass = 10.0f;
	debug = false;
}

bool Object::setModel(Model* m)
{
	mod = m;
	return true;
}

bool Object::setTexture(Texture* t)
{
	tex = t;
	return true;
}

bool Object::update(float dt)
{
	//velocity from force and time
	transform.velocity += (transform.force / transform.mass) * dt;
	//location from velocity
	transform.location += transform.velocity * dt;

	glm::mat4 rotation = glm::yawPitchRoll(transform.rotation.y, transform.rotation.x, transform.rotation.z);
	glm::mat4 translation = glm::translate(transform.location);
	glm::mat4 scale = glm::scale(transform.size);
	
	transform.modelWorld = translation * rotation * scale;

	//transform.velocity = { 0, 0, 0 };
	transform.force = { 0, 0, 0 };

	return true;
}

bool Object::render()
{
	//update(dt);
	glUniformMatrix4fv(9, 1, GL_FALSE, &transform.modelWorld[0][0]);
	tex->render();
	mod->render();
	return true;
}

bool Object::collidesWith(const Object& other)
{
	if (collider == nocollider || other.collider == nocollider) {
		return false;
	}
	//float dis = glm::length(other.transform.location - transform.location);
	glm::vec3 dis = other.transform.location - transform.location;
	//float dist = glm::distance(transform.location, other.transform.location);

	if (collider == sphere && other.collider == sphere) {
		/*if (glm::dot(dis, dis) > pow((transform.size.x + other.transform.size.x), 2)) {
			return false;
		}*/
		if (distance(transform.location, other.transform.location) > transform.size.x + other.transform.size.x) {
			return false;
		}
	}
	if (collider == aabb && other.collider == aabb) {
		if (glm::distance(transform.location.x, other.transform.location.x) > transform.size.x + other.transform.size.x) {
			return false;
		}
		if (glm::distance(transform.location.y, other.transform.location.y) > transform.size.y + other.transform.size.y) {
			return false;
		}
		if (glm::distance(transform.location.z, other.transform.location.z) > transform.size.z + other.transform.size.z) {
			return false;
		}
	}

	glm::vec3 cdist;
	glm::vec3 dp;

	if (collider == sphere && other.collider == aabb) {
		cdist = other.transform.location + glm::clamp(dis, -1.0f * other.transform.size.x, other.transform.size.x);
		dp = transform.location - cdist;
		if (glm::dot(dp, dp) > (transform.size.x * transform.size.x)) {
			return false;
		}
	}
	if (collider == aabb && other.collider == sphere){
		cdist = transform.location + glm::clamp(dis, -1.0f * transform.size.x, transform.size.x);
		dp = other.transform.location - cdist;
		if (glm::length(dp) > other.transform.size.x) {
			return false;
		}
	}
	if (debug) {
		printf("Collided when this was at x: %f, y: %f, z: %f\n", transform.location.x, transform.location.y, transform.location.z);
	}
	return true;
}


Object::~Object()
{
}
