#include "LogFiles.h"

#include "Engine/System/Tools.h"
#include "Engine/System/Debug/Assert.h"
#include "Engine/System/Debug/Log.h"

// std
#include <filesystem>
#include <iostream>

std::ofstream Hyko::LogF::m_file;
std::string Hyko::LogF::m_currTime;
std::string Hyko::LogF::m_filePath;
std::string Hyko::LogF::m_folderPath;
bool Hyko::LogF::m_hasError = false;

void Hyko::LogF::editFolderPath(std::string newPath)
{
	size_t pos;
	while ((pos = newPath.find("\\")) != std::string::npos)
		newPath.replace(pos, 1, "/");

	m_folderPath = newPath + "/";
	m_filePath = m_folderPath + m_currTime + ".hklog";
}

void Hyko::LogF::init()
{
	try{
		m_currTime = Hyko::Tools::getCurrentTime().c_str();
		// creating a temporary file name
		m_folderPath = "Hyko/log/";
		m_filePath = m_folderPath + m_currTime + ".hklog";

		if (std::filesystem::create_directory(m_folderPath)) HK_INFO("Log directory has been created");
		m_file.open(m_filePath, std::ios::app);

		if (m_file.is_open()) HK_INFO("Log file has been created");

		m_file << Hyko::Tools::getGPUAndGLInformations().c_str() << "\n\n";
		m_file.close();
	}
	catch(int x){
		HK_ERROR("x");
	}
}

void Hyko::LogF::deleteAllLogs()
{
	for (auto& i : std::filesystem::directory_iterator(m_folderPath))
		std::filesystem::remove_all(i.path());
}

void Hyko::LogF::addMsgToLog(const std::string msg, const char* filePath)
{
	try {
		m_file.open(m_filePath, std::ios::app);
		m_file << "[" << Hyko::Tools::getCurrentTime() << "] " << "(INFO)" << "\"" << msg << "\" (" << filePath << ")\n";
		m_file.close();
	}
	catch (int x) {
		HK_ERROR(x);
	}
}

void Hyko::LogF::addErrorMsgToLog(const std::string msg, const char* filePath)
{
	try {
		m_file.open(m_filePath, std::ios::app);
		m_file << "[" << Hyko::Tools::getCurrentTime() << "] " << "(ERROR)" << "\"" << msg << "\" (" << filePath << ")\n";
		m_file.close();
	}
	catch (int x) {
		HK_ERROR(x);
	}
}

void Hyko::LogF::shutdown()
{
	if(m_hasError == false) std::filesystem::remove(m_filePath);
}

/*
* A queue system is likely to be implemented in the future
*/
