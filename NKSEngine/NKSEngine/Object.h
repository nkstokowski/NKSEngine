#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <string>
#include <time.h>
#include "Model.h"
#include "Texture.h"

using namespace std;

struct Transform {
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 size;
	glm::vec3 force;
	glm::vec3 velocity;
	float mass;
	glm::mat4 modelWorld;
};


class Object
{
private:
public:
	enum ColliderTypes { nocollider, aabb, sphere, obb };
	bool debug;
	Transform transform;
	string tag;
	Model* mod;
	Texture* tex;
	ColliderTypes collider;
	Object();
	virtual bool setModel(Model* m);
	virtual bool setTexture(Texture* t);
	virtual bool update(float dt);
	virtual bool render();
	bool collidesWith(const Object& other);
	virtual ~Object();
};

