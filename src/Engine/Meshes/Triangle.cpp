#include "Triangle.h"
#include "../../shader.h"
#include "../../GL/VBO.h"
#include "../../GL/VAO.h"
#include "../ImGui/ImGuiWindows.h"
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

ImGuiWin GuiWin;

unsigned int Triangle::createShader(std::string vFilePath, std::string fFilePath)
{
	Shader shader;

	shader.loadVTextFile(vFilePath);
	shader.loadFTextFile(fFilePath);
	shader.createShader(vFilePath, fFilePath);
	shader.isCompileShader(vFilePath, fFilePath);
	shader.createShaderProgram(vFilePath, fFilePath);

	unsigned int shaderProgram;
	shaderProgram = shader.createShaderProgram(vFilePath, fFilePath);

	return shaderProgram;
}

unsigned int Triangle::createVBO()
{
	VBO VBO;

	unsigned int vbo;

	vbo = VBO.createVBO(vertices);

	return vbo;
}

unsigned int Triangle::createVAO()
{
	VAO VAO;

	unsigned int vao;

	vao = VAO.createVAO(vertices, createVBO());

	return vao;
}

glm::mat4 Triangle::translate(unsigned int shaderProgram, glm::vec3 newPos)
{
	translation = glm::mat4(1.0f);
	translation = glm::translate(translation, newPos);

	return translation;
}

glm::mat4 Triangle::setRotate(unsigned int shaderProgram, float newRotation, glm::vec3 axis)
{
	rotate = glm::mat4(1.0f);
	rotate = glm::rotate(rotate, glm::radians(newRotation), axis);

	return rotate;
}

glm::mat4 Triangle::setScale(unsigned int shaderProgram, glm::vec3 newScale)
{
	scale = glm::mat4(1.0f);
	scale = glm::scale(scale, newScale);

	return scale;
}

glm::mat4 Triangle::createTransformMatrix()
{
	glm::mat4 Transform;

	Transform = scale;
	Transform *= rotate;
	Transform *= translation;

	return Transform;
}

Triangle::~Triangle()
{
	unsigned int VAO = createVAO();
	unsigned int VBO = createVBO();

	glDisableVertexAttribArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
