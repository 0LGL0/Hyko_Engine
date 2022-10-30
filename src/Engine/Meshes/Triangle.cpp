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
	m_position = newPos;

	translation = glm::mat4(1.0f);
	translation = glm::translate(translation, m_position);

	return translation;
}

//glm::mat4 Triangle::Rotate(unsigned int shaderProgram, float newRotation, glm::vec3 axis)
//{
//	m_rotation = axis * newRotation;
//
//	rotate = glm::mat4(1.0f);
//	rotate = glm::rotate(rotate, glm::radians(newRotation), m_rotation / newRotation);
//
//	return rotate;
//}

glm::mat4 Triangle::Scale(unsigned int shaderProgram, glm::vec3 newScale)
{
	m_scale = newScale;

	scale = glm::mat4(1.0f);
	scale = glm::scale(scale, m_scale);

	return scale;
}

glm::mat4 Triangle::createTransformMatrix()
{
	glm::mat4 Transform;

	Transform = scale;
	Transform *= translation;

	return Transform;
}

void Triangle::getColorFromGUI()
{
	ImGuiWin GuiWindow;

	m_diffuseColor.r = GuiWindow.triangleColor[0];
	m_diffuseColor.g = GuiWindow.triangleColor[1];
	m_diffuseColor.b = GuiWindow.triangleColor[2];
	m_diffuseColor.a = GuiWindow.triangleColor[3];
}

Triangle::~Triangle()
{
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}
