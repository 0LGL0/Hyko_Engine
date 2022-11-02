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

unsigned int Shader::createVShader()
{
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(this->vertexShader, 1, &this->vShaderCode, NULL);

	glCompileShader(this->vertexShader);

	return this->vertexShader;
}

unsigned int Shader::createFShader()
{
	this->fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(this->fragShader, 1, &this->fShaderCode, NULL);

	glCompileShader(this->fragShader);

	return this->fragShader;
}

int Shader::isCompileShader()
{
	int vSuccess;
	int fSuccess;

	char infolog[512];

	glGetShaderiv(this->vertexShader, GL_COMPILE_STATUS, &vSuccess);
	glGetShaderiv(this->fragShader, GL_COMPILE_STATUS, &fSuccess);

	if (!vSuccess) {
		glGetShaderInfoLog(this->vertexShader, 512, NULL, infolog);
		std::cout << "Vertex shader not compilled " << infolog << std::endl;
		return -1;
	}

	if (!fSuccess) {
		glGetShaderInfoLog(this->fragShader, 512, NULL, infolog);
		std::cout << "Fragment shader not compilled " << infolog << std::endl;
		return -1;
	}

	return 0;
}

unsigned int Shader::createShaderProgram()
{
	int success;

	char infolog[512];

	this->shaderProgram = glCreateProgram();

	glAttachShader(this->shaderProgram, this->vertexShader);
	glAttachShader(this->shaderProgram, this->fragShader);
	glLinkProgram(this->shaderProgram);

	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infolog);
		std::cout << "Shader program is not compiled" << std::endl;
		return -1;
	}

	glDeleteShader(this->vertexShader);
	glDeleteShader(this->fragShader);

	return this->shaderProgram;
}