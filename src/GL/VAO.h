#pragma once
#include <vector>

class VAO {
public:
	unsigned int createVAO(std::vector<float> vertices, unsigned int VBO);

	void bind(unsigned int VAO);
};
