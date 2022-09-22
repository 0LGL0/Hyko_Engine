#pragma once

class Render {
public:
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	float vertices[12] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	unsigned int indexs[6] = {
		0, 1, 3,
		1, 2, 3
	};

	GLuint createVBO();
	GLuint createVAO();
	GLuint createEBO();

	~Render();
};
