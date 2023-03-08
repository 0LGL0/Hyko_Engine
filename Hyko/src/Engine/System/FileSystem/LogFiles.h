#pragma once

#include <fstream>
#include <string>

namespace Hyko {
	class LogF {
	private:
		static std::ofstream m_file;
		static std::string m_currTime;
		static std::string m_filePath;
		static std::string m_folderPath;

		static bool m_hasError;

		friend class ESettings;
	private:
		static bool editFolderPath(std::string newPath);
	public:
		static void init();

		static void addMsgToLog(const std::string msg, const char* filePath = __builtin_FILE());
		static void addErrorMsgToLog(const std::string msg, const char* filePath = __builtin_FILE());
		static void deleteAllLogs();

		static void shutdown();
	public: // setters
		void setFolderPath(const std::string path) { m_folderPath = path; }
	};
}