#pragma once

#include <fstream>
#include <string>

namespace Hyko {
	class LogF {
	private:
		static std::ofstream m_file;
		static std::string m_currTime;
		static std::string m_filePath;

		static bool m_hasError;
	public:
		static void init();

		static void addMsgToLog(const std::string msg, const char* filePath = __builtin_FILE());
		static void addErrorMsgToLog(const std::string msg, const char* filePath = __builtin_FILE());

		static void shutdown();
	};
}