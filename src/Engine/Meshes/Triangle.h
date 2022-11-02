#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

class Triangle {
private:
	glm::mat4 translation;
	glm::mat4 rotate;
	glm::mat4 scale;
private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
private:
	glm::vec4 m_diffuseColor;
private:
	unsigned int vbo;
	unsigned int vao;
private:
	void getColorFromGUI();
private:
	unsigned int createVBO();
public:
	std::vector<float> vertices = {
		 -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int createVAO();

	unsigned int createShader(std::string vFilePath, std::string fFilePath);

	glm::mat4 translate(unsigned int shaderProgram, glm::vec3 newPos);
	glm::mat4 Rotate(unsigned int shaderProgram, float newRotation, glm::vec3 axis);
	glm::mat4 Scale(unsigned int shaderProgram, glm::vec3 newScale);
	glm::mat4 createTransformMatrix();

	////getters//////////////////////////////////////////////////

	glm::vec3 getPosition() { return m_position; };
	glm::vec3 getRotation() { return m_rotation; };
	glm::vec3 getScale()	{ return m_scale; };

	glm::vec4 getDiffuseColor() { getColorFromGUI(); return m_diffuseColor; };

	/////////////////////////////////////////////////////////////

	////setters/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void setPosition(glm::vec3 newPos) { m_position = newPos; };
	void setPosition(float x, float y, float z) { m_position.x = x; m_position.y = y; m_position.z = z; };
	void setPosition(float x, float y) { m_position.x = x; m_position.y = y; m_position.z = 0.0f; };

	void setRotation(glm::vec3 newRot) { m_rotation = newRot; };
	void setRotation(float x, float y, float z) { m_rotation.x = x; m_rotation.y = y; m_rotation.z = z; };
	void setRotation(float x, float y) { m_rotation.x = x; m_rotation.y = y; m_rotation.z = 0.0f; };

	void setScale(glm::vec3 newScale)  { m_scale = newScale; };
	void setScale(float x, float y, float z) { m_scale.x = x; m_scale.y = y; m_scale.z = z; };
	void setScale(float x, float y) { m_scale.x = x; m_scale.y = y; m_scale.z = 0.0f; };

	void setDeffuseColor(glm::vec4 newDeffuseColor) { m_diffuseColor = newDeffuseColor; };
	void setDeffuseColor(float r, float g, float b, float a) { m_diffuseColor.r = r; m_diffuseColor.g = g; m_diffuseColor.b = b; m_diffuseColor.a = a; };

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	~Triangle();
};
