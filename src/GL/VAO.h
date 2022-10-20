#pragma once
#include <vector>

class VAO {
	unsigned int VAO;
	unsigned int vbo;
public:
	unsigned int createVAO(std::vector<float> vertices, unsigned int VBO);
};
