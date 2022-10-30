#pragma once
#include "glad/glad.h"
#include <string>
#include <fstream>

class Shader {
private:
	std::string VShaderFilePath;
	std::string FShaderFilePath;
private:
	std::string vShader;
	std::string fShader;
private:
	const char* vShaderCode;
	const char* fShaderCode;
private:
	unsigned int vertexShader;
	unsigned int fragShader;
	unsigned int shaderProgram;
public:
	const char *loadVTextFile(std::string vFilePath);
	const char *loadFTextFile(std::string fFilePath);

	unsigned int createVShader(std::string vFilePath);
	unsigned int createFShader(std::string fFilePath);

	unsigned int createShaderProgram(std::string vFilePath, std::string fFilePath);

	int isCompileShader(std::string vFilePath, std::string fFilePath);

	////getters/////////////////////////////////////////////////////////////

	unsigned int getShaderProgram() { return shaderProgram; };

	////////////////////////////////////////////////////////////////////////

};