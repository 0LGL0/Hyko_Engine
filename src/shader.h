#pragma once
#include "glad/glad.h"
#include <string>
#include <fstream>

class Shader {
public:
	std::string vShader;
	std::string fShader;

	const char* vShaderCode;
	const char* fShaderCode;

	unsigned int vertexShader;
	unsigned int fragShader;
	unsigned int shaderProgram;

	const char *loadVTextFile(std::string vFilePath);
	const char *loadFTextFile(std::string fFilePath);

	unsigned int createShader(std::string vFilePath, std::string fFilePath);

	int isCompileShader(std::string vFilePath, std::string fFilePath);

	unsigned int createShaderProgram(std::string vFilePath, std::string fFilePath);

};