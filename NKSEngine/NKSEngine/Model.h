#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <FreeImage.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <string>

using namespace std;

class Model 
{
private:
	GLuint vertArr;
	unsigned int vertCount;
	string objFile;
public:
	glm::vec3 maxXYZ;
	bool buffer();
	bool render();
	bool unload();
	Model(string filenm);
	virtual ~Model();
};

struct VertInd {
	unsigned int locInd;
	unsigned int uvInd;
	unsigned int normInd;
};

struct Vertex {
	glm::vec3 location;
	glm::vec2 uv;
	glm::vec3 normal;
};