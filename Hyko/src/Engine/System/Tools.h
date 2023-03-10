#pragma once

#include "Engine/System/Debug/Log.h"

// std
#include <string>

// GL
#include <glad/glad.h>

#define HK_GET_GPU_VENDOR		glGetString(GL_VENDOR)
#define HK_GET_GPU_RENDERER		glGetString(GL_RENDERER)
#define HK_GET_GL_VERSION		glGetString(GL_VERSION)
#define HK_GET_GLSL_VERSION		glGetString(GL_SHADING_LANGUAGE_VERSION)

#define HK_RETURN_MACRO(x) x
#define HK_RETURN_MACRO_STR(x) #x


namespace Hyko {
	class Tools {
	public:
		static void printGPUAndGLInformations(const bool transfer);
	public: // getters
		static std::string getGPUAndGLInformations(const bool transfer = false);
		static std::string getCurrentTime();
	};
}