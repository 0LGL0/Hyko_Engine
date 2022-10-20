#include "Triangle.h"
#include "../../shader.h"
#include "../../GL/VBO.h"
#include "../../GL/VAO.h"
#include "../ImGui/ImGuiWindows.h"
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

unsigned int Triangle::createShader(std::string vFilePath, std::string fFilePath)
{
	Shader shader;

	shader.loadVTextFile(vFilePath);
	shader.loadFTextFile(fFilePath);
	shader.createVShader(vFilePath);
	shader.createFShader(fFilePath);
	shader.isCompileShader(vFilePath, fFilePath);
	shader.createShaderProgram(vFilePath, fFilePath);

	unsigned int shaderProgram;
	shaderProgram = shader.createShaderProgram(vFilePath, fFilePath);

	return shaderProgram;
}

unsigned int Triangle::createVBO()
{
	VBO VBO;

	vbo = VBO.createVBO(vertices);

	return vbo;
}

unsigned int Triangle::createVAO()
{
	VAO VAO;

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
	Transform *= translation;

	return Transform;
}

glm::vec4 Triangle::getColorFromGUI()
{
	ImGuiWin GuiWindow;
	
	glm::vec4 outColor;

	outColor.x = GuiWindow.triangleColor[0];
	outColor.y = GuiWindow.triangleColor[1];
	outColor.z = GuiWindow.triangleColor[2];
	outColor.w = GuiWindow.triangleColor[3];

	return outColor;
}

Triangle::~Triangle()
{
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
