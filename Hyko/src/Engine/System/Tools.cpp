#include "Tools.h"

#include <ctime>

void Hyko::Tools::printGPUAndGLInformations(const bool transfer)
{
	HK_INFO(getGPUAndGLInformations(transfer));
}

std::string Hyko::Tools::getGPUAndGLInformations(const bool transfer)
{
	std::string info;

	switch (transfer) {
	case true:
		info = "**************************************************************\n\t\t\t\t\t\b\b\b"
			+ (std::string)"GPU vendor: " + (char*)HK_GET_GPU_VENDOR + "\n\t\t\t\t\t\b\b\b"
			+ "GPU name: " + (char*)HK_GET_GPU_RENDERER + "\n\t\t\t\t\t\b\b\b"
			+ "OpenGL version: " + (char*)HK_GET_GL_VERSION + "\n\t\t\t\t\t\b\b\b"
			+ "GLSL version: " + (char*)HK_GET_GLSL_VERSION + "\n\t\t\t\t\t\b\b\b"
			+ "**************************************************************";
		break;
	case false:
		info = "**************************************************************\n"
			+ (std::string)"GPU vendor: " + (char*)HK_GET_GPU_VENDOR + "\n"
			+ "GPU name: " + (char*)HK_GET_GPU_RENDERER + "\n"
			+ "OpenGL version: " + (char*)HK_GET_GL_VERSION + "\n"
			+ "GLSL version: " + (char*)HK_GET_GLSL_VERSION + "\n"
			+ "**************************************************************";
		break;
	}

	return info;
}

std::string Hyko::Tools::getCurrentTime()
{
	// buffers
	time_t  timer = time(0);
	tm		curTime;

	time(&timer);
	localtime_s(&curTime, &timer);

	return std::to_string(curTime.tm_mday) + "-" + std::to_string(1 + curTime.tm_mon) + "-" + std::to_string(1900 + curTime.tm_year) + "_"
		+ std::to_string(curTime.tm_hour) + "-" + std::to_string(curTime.tm_min) + "-" + std::to_string(curTime.tm_sec);
}