#include "shader.h"
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <sstream>

const char* Shader::loadVTextFile(std::string vFilePath)
{
	std::ifstream vs;

	this->VShaderFilePath = vFilePath;

	vs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vs.open(vFilePath);

		if (!vs.is_open()) {
			std::cout << "File of vertex shader not openned" << std::endl;
			return NULL;
		}

		std::stringstream vShaderStream;

		vShaderStream << vs.rdbuf();

		vs.close();

		this->vShader = vShaderStream.str();

		if (this->vShader.c_str() == NULL) {
			std::cout << "Vertex shader file not readed" << std::endl;
			return NULL;
		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::vSHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	this->vShaderCode = this->vShader.c_str();

	return this->vShaderCode;
}

const char* Shader::loadFTextFile(std::string fFilePath)
{
	std::ifstream fs;

	this->FShaderFilePath = fFilePath;

	fs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {

		fs.open(fFilePath);

		if (!fs.is_open()) {
			std::cout << "File of fragment shader not openned" << std::endl;
			return NULL;
		}

		std::stringstream fShaderStream;


		fShaderStream << fs.rdbuf();


		fs.close();


		this->fShader = fShaderStream.str();

		if (this->fShader.c_str() == NULL) {
			std::cout << "Fragment shader file not readed" << std::endl;
			return NULL;
		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}


	this->fShaderCode = this->fShader.c_str();

	return this->fShaderCode;
}

unsigned int Shader::createVShader(const char* vSrc)
{
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(this->vertexShader, 1, &vSrc, NULL);

	glCompileShader(this->vertexShader);

	isCompileShader(vertexShader);

	return this->vertexShader;
}

unsigned int Shader::createFShader(const char* fSrc)
{
	this->fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(this->fragShader, 1, &fSrc, NULL);

	glCompileShader(this->fragShader);

	isCompileShader(fragShader);

	return this->fragShader;
}

int Shader::isCompileShader(unsigned int shader)
{
	int success;

	char infolog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infolog);
		std::cout << shader << ": " << "shader not compilled " << infolog << std::endl;
		return -1;
	}
	else std::cout << shader << ": " << "shader compiled" << std::endl;

	return 0;
}

unsigned int Shader::createShaderProgram(std::string vFilePath, std::string fFilePath)
{
	unsigned int vShader = createVShader(loadVTextFile(vFilePath));
	unsigned int fShader = createFShader(loadVTextFile(fFilePath));

	this->m_shaderProgram = glCreateProgram();

	glAttachShader(this->m_shaderProgram, vShader);
	glAttachShader(this->m_shaderProgram, fShader);
	glLinkProgram(this->m_shaderProgram);

	isCompileShader(m_shaderProgram);

	glDeleteShader(this->vertexShader);
	glDeleteShader(this->fragShader);

	return this->m_shaderProgram;
}

void Shader::use()
{
	glUseProgram(this->m_shaderProgram);
}

void Shader::unUse()
{
	glUseProgram(0);
}

void Shader::setUniformMat4(const char* name, const glm::mat4 value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniformMat3(const char* name, const glm::mat3 value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniformMat2(const char* name, const glm::mat2 value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUnifromf(const char* name, const float value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniform1f(location, value);
}

void Shader::setUnifrom2f(const char* name, const glm::vec2 value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniform2f(location, value.x, value.y);
}

void Shader::setUnifrom3f(const char* name, const glm::vec3 value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setUnifrom4f(const char* name, const glm::vec4 value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::setUnifromi(const char* name, const int value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniform1i(location, value);
}

void Shader::setUnifrom2i(const char* name, const glm::vec2 value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniform2i(location, value.x, value.y);
}

void Shader::setUnifrom3i(const char* name, const glm::vec3 value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniform3i(location, value.x, value.y, value.z);
}

void Shader::setUnifrom4i(const char* name, const glm::vec4 value)
{
	unsigned int location = glGetUniformLocation(m_shaderProgram, name);
	glUniform4i(location, value.x, value.y, value.z, value.w);
}
