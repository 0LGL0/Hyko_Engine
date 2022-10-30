#include "shader.h"
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <sstream>

const char* Shader::loadVTextFile(std::string vFilePath)
{
	std::ifstream vs;

	VShaderFilePath = vFilePath;

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

		vShader = vShaderStream.str();

		if (vShader.c_str() == NULL) {
			std::cout << "Vertex shader file not readed" << std::endl;
			return NULL;
		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::vSHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	vShaderCode = vShader.c_str();

	return vShaderCode;
}

const char* Shader::loadFTextFile(std::string fFilePath)
{
	std::ifstream fs;

	FShaderFilePath = fFilePath;

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


		fShader = fShaderStream.str();

		if (fShader.c_str() == NULL) {
			std::cout << "Fragment shader file not readed" << std::endl;
			return NULL;
		}
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}


	fShaderCode = fShader.c_str();

	return fShaderCode;
}

unsigned int Shader::createVShader(std::string vFilePath)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	

	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	

	glCompileShader(vertexShader);
	

	return vertexShader;
}

unsigned int Shader::createFShader(std::string fFilePath)
{
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragShader, 1, &fShaderCode, NULL);

	glCompileShader(fragShader);

	return fragShader;
}

int Shader::isCompileShader(std::string vFilePath, std::string fFilePath)
{
	int vSuccess;
	int fSuccess;

	char infolog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vSuccess);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fSuccess);

	if (!vSuccess) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "Vertex shader not compilled " << infolog << std::endl;
		std::cout << vShaderCode << std::endl;
		return -1;
	}

	if (!fSuccess) {
		glGetShaderInfoLog(fragShader, 512, NULL, infolog);
		std::cout << "Fragment shader not compilled " << infolog << std::endl;
		return -1;
	}

	return 0;
}

unsigned int Shader::createShaderProgram(std::string vFilePath, std::string fFilePath)
{
	int success;

	char infolog[512];

	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		std::cout << "Shader program is not compiled" << std::endl;
		return -1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

	return shaderProgram;
}