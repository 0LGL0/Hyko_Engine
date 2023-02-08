#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <assert.h>

namespace Hyko {
	class Log {
	private:
		static std::shared_ptr<spdlog::logger> m_logger;
	public:
		Log() = default;

		static void init();

		static std::shared_ptr<spdlog::logger>& getLogger() { return m_logger; }
	};
}

#define HK_ERROR(...)		::Hyko::Log::getLogger()->error(__VA_ARGS__)
#define HK_WARN(...)		::Hyko::Log::getLogger()->warn(__VA_ARGS__)
#define HK_INFO(...)		::Hyko::Log::getLogger()->info(__VA_ARGS__)
#define HK_TRACE(...)		::Hyko::Log::getLogger()->trace(__VA_ARGS__)
#define HK_CRITICAL(...)	::Hyko::Log::getLogger()->critical(__VA_ARGS__)