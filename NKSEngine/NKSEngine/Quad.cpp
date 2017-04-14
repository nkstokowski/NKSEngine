#include "Quad.h"


Quad::Quad()
{
	tag = "myobjtag";
}

void Quad::update()
{
	//printf("Updating at time: %f\n", Engine::timer.t);
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);
}

bool Quad::loadModel()
{
	vector<glm::vec3> locs = { { .9, .9, 0 },
	{ -.9, .9, 0 },
	{ -.9, -.9, 0 },
	{ .9, -.9, 0 } };

	vector <unsigned int> locInds = { 0, 1, 2, 0, 2, 3 };

	vertCount = locInds.size();

	vector<glm::vec3> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++) {
		vertBufData[i] = locs[locInds[i]];
	}
	GLuint vertBuf;

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertCount, &vertBufData[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glBindVertexArray(0);
	return true;
}


Quad::~Quad()
{
}
