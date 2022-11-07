#include "Triangle.h"
#include "../../shader.h"
#include "../../GL/VBO.h"
#include "../../GL/VAO.h"
#include "../ImGui/ImGuiWindows.h"
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

////functions for create triangle////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Triangle::createTriangle()
{
	this->m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_scale = glm::vec3(0.5f, 0.5f, 0.5f);
	this->m_diffuseColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glBindVertexArray(this->createVAO());
}

void Triangle::createTriangle(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec4 diffuseColor)
{
	this->m_position = pos;
	this->m_rotation = rot;
	this->m_scale = scale;
	this->m_diffuseColor = diffuseColor;

	glBindVertexArray(this->createVAO());
}

void Triangle::createTriangle(glm::vec2 pos, glm::vec3 rot, glm::vec2 scale, glm::vec4 diffuseColor)
{
	this->m_position = glm::vec3(pos, 0.0f);
	this->m_rotation = rot;
	this->m_scale = glm::vec3(scale, 0.0f);
	this->m_diffuseColor = diffuseColor;

	glBindVertexArray(this->createVAO());
}

void Triangle::createTriangle(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, float colorR, float colorG, float colorB, float colorA)
{
	this->m_position = glm::vec3(posX, posY, posZ);
	this->m_rotation = glm::vec3(rotX, rotY, rotZ);
	this->m_scale = glm::vec3(scaleX, scaleY, scaleZ);
	this->m_diffuseColor = glm::vec4(colorR, colorG, colorB, colorA);

	glBindVertexArray(this->createVAO());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int Triangle::createVBO()
{
	VBO VBO;

	this->vbo = VBO.createVBO(vertices, 3);

	return this->vbo;
}

unsigned int Triangle::createVAO()
{
	VAO VAO;

	this->vao = VAO.createVAO(vertices, this->createVBO());

	return this->vao;
}

glm::mat4 Triangle::translate(glm::vec3 newPos)
{
	this->m_position = newPos;

	this->translation = glm::mat4(1.0f);
	this->translation = glm::translate(this->translation, this->m_position);

	return this->translation;
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

glm::mat4 Triangle::Scale(glm::vec3 newScale)
{
	this->m_scale = newScale;

	this->scale = glm::mat4(1.0f);
	this->scale = glm::scale(scale, m_scale);

	return this->scale;
}

glm::mat4 Triangle::createTransformMatrix()
{
	glm::mat4 Transform;

	Transform = this->scale;
	Transform *= this->translation;

	return Transform;
}

void Triangle::getColorFromGUI()
{
	extern ImGuiWin GuiWindow;

	this->m_diffuseColor.r = GuiWindow.m_triangleColor[0];
	this->m_diffuseColor.g = GuiWindow.m_triangleColor[1];
	this->m_diffuseColor.b = GuiWindow.m_triangleColor[2];
	this->m_diffuseColor.a = GuiWindow.m_triangleColor[3];
}

////setters////////////////////////////////////////////////////////////////////////////////////////

void Triangle::setPosition(glm::vec3 newPos)
{
	extern ImGuiWin GuiWindow;

	GuiWindow.setMeshPosition(newPos);
	m_position = newPos;
}

void Triangle::setPosition(float x, float y, float z)
{
	extern ImGuiWin GuiWindow;

	GuiWindow.setMeshPosition(glm::vec3(x, y, z));
	m_position = glm::vec3(x, y, z);
}

void Triangle::setPosition(float x, float y)
{
	extern ImGuiWin GuiWindow;

	GuiWindow.setMeshPosition(glm::vec3(x, y, 0.0f));
	m_position = glm::vec3(x, y, 0.0f);
}

void Triangle::setScale(glm::vec3 newScale)
{
	extern ImGuiWin GuiWindow;

	GuiWindow.setMeshScale(newScale);
	m_scale = newScale;
}

void Triangle::setScale(float x, float y, float z)
{
	extern ImGuiWin GuiWindow;

	GuiWindow.setMeshScale(glm::vec3(x, y, z));
	m_scale = glm::vec3(x, y, z);
}

void Triangle::setScale(float x, float y)
{
	extern ImGuiWin GuiWindow;

	GuiWindow.setMeshScale(glm::vec3(x, y, 0.0f));
	m_scale = glm::vec3(x, y, 0.0f);
}

void Triangle::setDeffuseColor(glm::vec4 newDeffuseColor)
{
	extern ImGuiWin GuiWindow;

	GuiWindow.setMeshDiffuseColor(newDeffuseColor);
	m_diffuseColor = newDeffuseColor;
}

void Triangle::setDeffuseColor(float r, float g, float b, float a)
{
	extern ImGuiWin GuiWindow;

	GuiWindow.setMeshDiffuseColor(glm::vec4(r, g, b, a));
	m_diffuseColor = glm::vec4(r, g, b, a);
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Triangle::meshRender(unsigned int shaderProgram)
{
	extern ImGuiWin GuiWindow;

	glUseProgram(shaderProgram);

	this->Scale(GuiWindow.m_triangleNewScale);
	this->translate(GuiWindow.m_triangleNewPos);

	this->transUniformLocation = glGetUniformLocation(shaderProgram, "transform");
	glUniformMatrix4fv(this->transUniformLocation, 1, GL_FALSE, glm::value_ptr(this->createTransformMatrix()));

	this->colorUniformLocation = glGetUniformLocation(shaderProgram, "inColor");
	glUniform4f(this->colorUniformLocation, this->getDiffuseColor().r, this->getDiffuseColor().g, this->getDiffuseColor().b, this->getDiffuseColor().a);

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

Triangle::~Triangle()
{
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &this->vbo);
	glDeleteVertexArrays(1, &this->vao);
}
