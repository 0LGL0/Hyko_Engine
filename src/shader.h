#pragma once
#include "glad/glad.h"
#include <string>
#include <fstream>

class Shader {
	std::string VShaderFilePath;
	std::string FShaderFilePath;
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

	unsigned int createVShader(std::string vFilePath);
	unsigned int createFShader(std::string fFilePath);

	unsigned int createShaderProgram(std::string vFilePath, std::string fFilePath);

	int isCompileShader(std::string vFilePath, std::string fFilePath);

	void updateFragShader();

	~Shader();

};