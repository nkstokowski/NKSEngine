#include "Model.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

bool Model::buffer(string objFile)
{
	vector<glm::vec3> locs;
	vector<glm::vec2> uvs;
	vector<glm::vec3> normals;
	vector<VertInd> vertInds;

	ifstream strm(objFile, ios::binary);
	if (!strm.is_open()) {
		printf("Error opening file.\n");
		return false;
	}

	string line, label;
	float x, y, z;
	unsigned int a, b, c;
	char slash;

	while (getline(strm, line)) {
		istringstream ss(line);
		ss >> label;
		if (label.compare("v") == 0) {
			ss >> x >> y >> z;
			locs.push_back(glm::vec3(x, y, z));
		}
		else if (label.compare("vt") == 0) {
			ss >> x >> y;
			uvs.push_back(glm::vec2(x, y));
		}
		else if (label.compare("vn") == 0) {
			ss >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		else if (label.compare("f") == 0) {
			for (int i = 0; i < 3; i++) {
				ss >> a >> slash >> b >> slash >> c;
				VertInd res;
				res.locInd = a - 1;
				res.uvInd = b - 1;
				res.normInd = c - 1;

				vertInds.push_back(res);
			}
		}
	}
	strm.close();

	vertCount = vertInds.size();

	vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++) {
		vertBufData[i] = { locs[vertInds[i].locInd],
						   uvs[vertInds[i].uvInd],
						   normals[vertInds[i].normInd] };
	}
	GLuint vertBuf;

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertCount, &vertBufData[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glBindVertexArray(0);

	GLintptr vertex_normal_offset = 5 * sizeof(float);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)vertex_normal_offset);
	glBindVertexArray(1);

	return true;
}

bool Model::render()
{
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);
	return true;
}

Model::Model()
{
	vertArr = 0;
	vertCount = 0;
}


Model::~Model()
{
}
