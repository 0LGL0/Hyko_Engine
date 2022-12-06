#pragma once
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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
	unsigned int m_shaderProgram;
private:
	const char* loadVTextFile(std::string vFilePath);
	const char* loadFTextFile(std::string fFilePath);

	unsigned int createVShader(const char* vSrc);
	unsigned int createFShader(const char* fSrc);

	int isCompileShader(unsigned int shader);
public:

	unsigned int createShaderProgram(std::string vFilePath, std::string fFilePath);

	void use();
	void unUse();

	////setters/////////////////////////////////////////////////////////////

	void setUniformMat4(const char* name, const glm::mat4 value);
	void setUniformMat3(const char* name, const glm::mat3 value);
	void setUniformMat2(const char* name, const glm::mat2 value);

	void setUnifromf(const char* name, const float value);
	void setUnifrom2f(const char* name, const glm::vec2 value);
	void setUnifrom3f(const char* name, const glm::vec3 value);
	void setUnifrom4f(const char* name, const glm::vec4 value);

	void setUnifromi(const char* name, const int value);
	void setUnifrom2i(const char* name, const glm::vec2 value);
	void setUnifrom3i(const char* name, const glm::vec3 value);
	void setUnifrom4i(const char* name, const glm::vec4 value);

	////////////////////////////////////////////////////////////////////////

	////getters/////////////////////////////////////////////////////////////

	unsigned int getShaderProgram() { return m_shaderProgram; };

	std::string getVertexShaderFilePath() { return VShaderFilePath; };
	std::string getFragmentShaderFilePath() { return FShaderFilePath; };

	////////////////////////////////////////////////////////////////////////

};