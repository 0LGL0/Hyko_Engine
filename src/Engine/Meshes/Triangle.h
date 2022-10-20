#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

class Triangle {
public:
	std::vector<float> vertices = {
		 -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	glm::mat4 translation;
	glm::mat4 rotate;
	glm::mat4 scale;

	unsigned int vbo;
	unsigned int vao;

	unsigned int createShader(std::string vFilePath, std::string fFilePath);

	unsigned int createVBO();
	unsigned int createVAO();

	glm::mat4 translate(unsigned int shaderProgram, glm::vec3 newPos);
	glm::mat4 setRotate(unsigned int shaderProgram, float newRotation, glm::vec3 axis);
	glm::mat4 setScale(unsigned int shaderProgram, glm::vec3 newScale);
	glm::mat4 createTransformMatrix();

	glm::vec4 getColorFromGUI();

	~Triangle();
};
