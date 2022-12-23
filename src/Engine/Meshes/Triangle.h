#pragma once

#include "../GL/VO.h"

#include <string>
#include <vector>
#include <glm/glm.hpp>

class Triangle {
public:
	VO vo;
private:
	glm::mat4 translation;
	glm::mat4 rotate;
	glm::mat4 scale;
private:
	/*glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;*/
private:
	/*glm::vec4 m_diffuseColor;*/
private:
	unsigned int vertexObj;

	unsigned int m_shaderProgram;

	unsigned int transUniformLocation;
	unsigned int colorUniformLocation;
private:
	void getColorFromGUI();
private:
	void createVO();
public:
	
private:
	glm::mat4 translate(glm::vec3 newPos);
	/*glm::mat4 Rotate(float newRotation, glm::vec3 axis);*/
	glm::mat4 Scale(glm::vec3 newScale);
	glm::mat4 createTransformMatrix();
public:
	/*void createTriangle();
	void createTriangle(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, glm::vec4 diffuseColor);
	void createTriangle(glm::vec2 pos, glm::vec3 rot, glm::vec2 scale, glm::vec4 diffuseColor);
	void createTriangle(float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, float colorR, float colorG, float colorB, float colorA);*/

	

	/*Triangle();
	Triangle(glm::vec3 pos = { 0.0f, 0.0f, 0.0f }, glm::vec3 rot = { 0.0f, 0.0f, 0.0f }, glm::vec3 scale = { 0.5f, 0.5f, 0.0f }, glm::vec4 diffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f });
	Triangle(glm::vec2 pos = { 0.0f, 0.0f }, glm::vec3 rot = { 0.0f, 0.0f, 0.0f }, glm::vec2 scale = { 0.5f, 0.5f }, glm::vec4 diffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f });
	Triangle(float posX = 0.0f, float posY = 0.0f, float posZ = 0.0f, float rotX = 0.0f, float rotY = 0.0f, float rotZ = 0.0f, float scaleX = 0.5f, float scaleY = 0.5f, float scaleZ = 0.0f, float colorR = 1.0f, float colorG = 1.0f, float colorB = 1.0f, float colorA = 1.0f);*/
public:
	////getters/////////////////////////////////////////////////////////////////////////////////

	/*glm::vec3 getPosition() { return this->m_position; };
	glm::vec3 getRotation() { return this->m_rotation; };
	glm::vec3 getScale() { return this->m_scale; };

	glm::vec4 getDiffuseColor() { this->getColorFromGUI(); return this->m_diffuseColor; };*/

	unsigned int getShaderProgram() { return this->m_shaderProgram; };
	//unsigned int getVAO() { return this->vo.getVAO(); };

	////////////////////////////////////////////////////////////////////////////////////////////

	////setters////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*void setPosition(glm::vec3 newPos);
	void setPosition(float x, float y, float z);
	void setPosition(float x, float y);

	void setRotation(glm::vec3 newRot) { this->m_rotation = newRot; };
	void setRotation(float x, float y, float z) { this->m_rotation.x = x; this->m_rotation.y = y; this->m_rotation.z = z; };
	void setRotation(float x, float y) { this->m_rotation.x = x; this->m_rotation.y = y; this->m_rotation.z = 0.0f; };

	void setScale(glm::vec3 newScale);
	void setScale(float x, float y, float z);
	void setScale(float x, float y);

	void setDeffuseColor(glm::vec4 newDeffuseColor);
	void setDeffuseColor(float r, float g, float b, float a);*/

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void meshRender(unsigned int shaderProgram);	//function for render triangle
};
