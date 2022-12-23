#include "Triangle.h"
#include "../../shader.h"
#include "../ImGui/ImGuiWindows.h"
#include <iostream>
#include <glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ImGuiWin gui;

////functions for create triangle////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void Triangle::createTriangle()
//{
//	this->m_position = glm::vec3(0.0f, 0.0f, 0.0f);
//	this->m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
//	this->m_scale = glm::vec3(0.5f, 0.5f, 0.0f);
//	this->m_diffuseColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//
//	gui.setMeshPosition(glm::vec3(0.0f, 0.0f, 0.0f));
//	gui.setMeshScale(glm::vec3(0.5f, 0.5f, 0.0f));
//	gui.setMeshDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//
//	this->createVO();
//}
//
//void Triangle::createTriangle(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec4 diffuseColor)
//{
//	this->m_position = pos;
//	this->m_rotation = rot;
//	this->m_scale = scale;
//	this->m_diffuseColor = diffuseColor;
//
//	gui.setMeshPosition(pos);
//	gui.setMeshScale(scale);
//	gui.setMeshDiffuseColor(diffuseColor);
//
//	this->createVO();
//}
//
//void Triangle::createTriangle(glm::vec2 pos, glm::vec3 rot, glm::vec2 scale, glm::vec4 diffuseColor)
//{
//	this->m_position = glm::vec3(pos, 0.0f);
//	this->m_rotation = rot;
//	this->m_scale = glm::vec3(scale, 0.0f);
//	this->m_diffuseColor = diffuseColor;
//
//	gui.setMeshPosition(glm::vec3(pos, 0.0f));
//	gui.setMeshScale(glm::vec3(scale, 0.0f));
//	gui.setMeshDiffuseColor(diffuseColor);
//
//	createVO();
//}
//
//void Triangle::createTriangle(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, float colorR, float colorG, float colorB, float colorA)
//{
//	this->m_position = glm::vec3(posX, posY, posZ);
//	this->m_rotation = glm::vec3(rotX, rotY, rotZ);
//	this->m_scale = glm::vec3(scaleX, scaleY, scaleZ);
//	this->m_diffuseColor = glm::vec4(colorR, colorG, colorB, colorA);
//
//	gui.setMeshPosition(glm::vec3(posX, posY, posZ));
//	gui.setMeshScale(glm::vec3(scaleX, scaleY, scaleZ));
//	gui.setMeshDiffuseColor(glm::vec4(colorR, colorG, colorB, colorA));
//
//	createVO();
//}

//Triangle::Triangle()
//{
//	setPosition(0.0f, 0.0f, 0.0f);
//	setRotation(0.0f, 0.0f, 0.0f);
//	setScale(0.0f, 0.0f, 0.0f);
//	setDiffuseColor(0.0f, 0.0f, 0.0f, 0.0f);
//}
//
//Triangle::Triangle(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec4 diffuseColor)
//{
//	setPosition(pos);
//	setRotation(rot);
//	setScale(scale);
//	setDiffuseColor(diffuseColor);
//}
//
//Triangle::Triangle(glm::vec2 pos, glm::vec3 rot, glm::vec2 scale, glm::vec4 diffuseColor)
//{
//	setPosition({ pos, 0.0f });
//	setRotation(rot);
//	setScale({ scale, 0.0f });
//	setDiffuseColor(diffuseColor);
//}
//
//Triangle::Triangle(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, float colorR, float colorG, float colorB, float colorA)
//{
//	setPosition(posX, posY, posZ);
//	setRotation(rotX, rotY, rotZ);
//	setScale(scaleX, scaleY, scaleZ);
//	setDiffuseColor(colorR, colorG, colorB, colorA);
//}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void Triangle::createVO()
//{
//	vo.createVertexObjects(vertices, 3, indices);
//
//	vertexObj = vo.getVAO();
//}
//
//glm::mat4 Triangle::translate(glm::vec3 newPos)
//{
//	this->m_position = newPos;
//
//	this->translation = glm::mat4(1.0f);
//	this->translation = glm::translate(this->translation, this->m_position);
//
//	return this->translation;
//}
//
////glm::mat4 Triangle::Rotate(unsigned int shaderProgram, float newRotation, glm::vec3 axis)
////{
////	m_rotation = axis * newRotation;
////
////	rotate = glm::mat4(1.0f);
////	rotate = glm::rotate(rotate, glm::radians(newRotation), m_rotation / newRotation);
////
////	return rotate;
////}
//
//glm::mat4 Triangle::Scale(glm::vec3 newScale)
//{
//	this->m_scale = newScale;
//
//	this->scale = glm::mat4(1.0f);
//	this->scale = glm::scale(scale, m_scale);
//
//	return this->scale;
//}
//
//glm::mat4 Triangle::createTransformMatrix()
//{
//	glm::mat4 Transform;
//
//	Transform = this->scale;
//	Transform *= this->translation;
//
//	return Transform;
//}
//
//void Triangle::getColorFromGUI()
//{
//	this->m_diffuseColor.r = gui.m_triangleColor[0];
//	this->m_diffuseColor.g = gui.m_triangleColor[1];
//	this->m_diffuseColor.b = gui.m_triangleColor[2];
//	this->m_diffuseColor.a = gui.m_triangleColor[3];
//}
//
//////setters////////////////////////////////////////////////////////////////////////////////////////
//
//void Triangle::setPosition(glm::vec3 newPos)
//{
//	gui.setMeshPosition(newPos);
//	m_position = newPos;
//}
//
//void Triangle::setPosition(float x, float y, float z)
//{
//
//	gui.setMeshPosition(glm::vec3(x, y, z));
//	m_position = glm::vec3(x, y, z);
//}
//
//void Triangle::setPosition(float x, float y)
//{
//	gui.setMeshPosition(glm::vec3(x, y, 0.0f));
//	m_position = glm::vec3(x, y, 0.0f);
//}
//
//void Triangle::setScale(glm::vec3 newScale)
//{
//	gui.setMeshScale(newScale);
//	m_scale = newScale;
//}
//
//void Triangle::setScale(float x, float y, float z)
//{
//	gui.setMeshScale(glm::vec3(x, y, z));
//	m_scale = glm::vec3(x, y, z);
//}
//
//void Triangle::setScale(float x, float y)
//{
//	gui.setMeshScale(glm::vec3(x, y, 0.0f));
//	m_scale = glm::vec3(x, y, 0.0f);
//}
//
//void Triangle::setDeffuseColor(glm::vec4 newDeffuseColor)
//{
//	gui.setMeshDiffuseColor(newDeffuseColor);
//	m_diffuseColor = newDeffuseColor;
//}
//
//void Triangle::setDeffuseColor(float r, float g, float b, float a)
//{
//	gui.setMeshDiffuseColor(glm::vec4(r, g, b, a));
//	m_diffuseColor = glm::vec4(r, g, b, a);
//}
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

