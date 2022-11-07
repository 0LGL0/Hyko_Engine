#pragma once
#include <vector>

class VBO {
	unsigned int VBO;
public:
	unsigned int createVBO(std::vector<float> vertices, int8_t count);
};