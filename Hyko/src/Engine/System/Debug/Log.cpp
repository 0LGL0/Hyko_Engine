#include "Log.h"

std::shared_ptr<spdlog::logger> Hyko::Log::m_logger;

void Hyko::Log::init()
{
	spdlog::set_pattern("[%Y-%m-%d / %T] %^(%l) %n: %v%$");

	m_logger = spdlog::stdout_color_mt("Hyko");
	m_logger->set_level(spdlog::level::trace);
}
